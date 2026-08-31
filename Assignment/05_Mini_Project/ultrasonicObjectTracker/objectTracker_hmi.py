"""
import re
from collections import defaultdict
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import serial


def parse_telemetry(line):
  #Extract track data from telemetry line.#
  pattern = (
      r"ID:(\d+).*Dist:\s*(\d+)mm.*Angle:\s*(\d+).*Vel:\s*(-?\d+).*Conf:(\d+)"
  )
  match = re.search(pattern, line)
  if match:
    return {
        "id": int(match.group(1)),
        "distance_mm": int(match.group(2)),
        "bearing_deg": int(match.group(3)),
        "velocity": int(match.group(4)),
        "confidence": int(match.group(5)),
    }
  return None


class RadarDisplay:

  def __init__(self, com_port="COM3", baud_rate=9600):
    self.ser = serial.Serial(com_port, baud_rate, timeout=0.1)
    self.tracks = {}  # {track_id: track_data}

    # Create figure with polar projection
    self.fig = plt.figure(figsize=(10, 10))
    self.ax = self.fig.add_subplot(111, projection="polar")

    # Animation
    self.anim = FuncAnimation(self.fig, self.update, interval=100, blit=False)

  def setup_polar_axis(self):
    #Re-applies orientation and range limits after clearing.#
    self.ax.clear()
    self.ax.set_theta_offset(np.pi / 2)  # 0° at Top (North)
    self.ax.set_theta_direction(-1)  # Clockwise
    self.ax.set_ylim(0, 4000)  # Max distance in mm
    self.ax.set_rlabel_position(45)
    self.ax.set_title("Ultrasonic Radar Tracker", pad=20)

  def update(self, frame):
    #Drain serial queue and refresh the polar plot.#
    while self.ser.in_waiting:
      line = self.ser.readline().decode("utf-8", errors="ignore").strip()
      if line.startswith("ID:"):
        track = parse_telemetry(line)
        if track:
          self.tracks[track["id"]] = track

    self.setup_polar_axis()

    # Plot each active track
    for track_id, track in self.tracks.items():
      bearing_rad = np.radians(track["bearing_deg"])
      distance_mm = track["distance_mm"]
      confidence = np.clip(track["confidence"], 0, 100)

      # Color by confidence (green=100%, red=0%)
      color = plt.cm.RdYlGn(confidence / 100.0)

      # Plot detection point
      self.ax.plot(bearing_rad, distance_mm, "o", markersize=10, color=color)

      # Target label
      self.ax.text(
          bearing_rad,
          distance_mm + 200,
          f"ID:{track_id} ({track['velocity']}mm/s)",
          fontsize=8,
          ha="center",
      )

      # Velocity Vector using polar-safe annotation
      if track["velocity"] != 0:
        vel_scale = 0.2
        target_dist = distance_mm + (track["velocity"] * vel_scale)
        self.ax.annotate(
            "",
            xy=(bearing_rad, target_dist),
            xytext=(bearing_rad, distance_mm),
            arrowprops=dict(
                arrowstyle="->", color="blue", lw=1.5, alpha=0.6
            ),
        )

    return []

  def run(self):
    #Display the plot.#
    plt.show()


if __name__ == "__main__":
  radar = RadarDisplay(com_port="COM3", baud_rate=9600)
  radar.run()
"""

import re
import serial

def parse_telemetry(line):
    """Extract track data from telemetry line."""
    pattern = r'ID:(\d+).*Dist:\s*(\d+)mm.*Angle:\s*(\d+).*Vel:\s*(-?\d+).*Conf:(\d+)'
    match = re.search(pattern, line)
    if match:
        return {
            'id': int(match.group(1)),
            'distance_mm': int(match.group(2)),
            'bearing_deg': int(match.group(3)),
            'velocity': int(match.group(4)),
            'confidence': int(match.group(5))
        }
    return None

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
from collections import defaultdict

class RadarDisplay:
    def __init__(self, com_port='COM3', baud_rate=9600):
        self.ser = serial.Serial(com_port, baud_rate, timeout=1)
        self.tracks = {}  # {track_id: track_data}
        
        # Create figure with polar projection
        self.fig = plt.figure(figsize=(10, 10))
        self.ax = self.fig.add_subplot(111, projection='polar')
        
        # Configure axes
        self.ax.set_theta_offset(np.pi/2)  # 0° at top
        self.ax.set_theta_direction(-1)    # Clockwise
        self.ax.set_ylim(0, 4000)          # Max distance in mm
        self.ax.set_rlabel_position(45)
        self.ax.set_title('Ultrasonic Radar Tracker', pad=20)
        
        # Animation
        self.anim = FuncAnimation(self.fig, self.update, interval=100, blit=False)
        
    def update(self, frame):
        """Called ~10x per second to refresh the plot."""
        if self.ser.in_waiting:
            line = self.ser.readline().decode('utf-8', errors='ignore').strip()
            if line.startswith('ID:'):
                track = parse_telemetry(line)
                if track:
                    self.tracks[track['id']] = track
        
        # Clear and redraw
        self.ax.clear()
        self.ax.set_theta_offset(np.pi/2)
        self.ax.set_theta_direction(-1)
        self.ax.set_ylim(0, 4000)
        self.ax.set_title('Ultrasonic Radar Tracker')
        
        # Plot each track
        for track_id, track in self.tracks.items():
            bearing_rad = np.radians(track['bearing_deg'])
            distance_mm = track['distance_mm']
            confidence = track['confidence']
            
            # Color by confidence (green=100%, red=0%)
            color = plt.cm.RdYlGn(confidence / 100.0)
            
            # Plot point
            self.ax.plot(bearing_rad, distance_mm, 'o', markersize=10, color=color)
            
            # Label with track ID
            self.ax.text(bearing_rad, distance_mm + 200, f'ID:{track_id}', 
                        fontsize=8, ha='center')
            
            # Optional: velocity vector (arrow in direction of motion)
            if track['velocity'] != 0:
                vel_scale = 0.1  # Scale velocity magnitude for visibility
                self.ax.arrow(bearing_rad, distance_mm, 0, track['velocity'] * vel_scale,
                             head_width=0.1, head_length=100, fc='blue', ec='blue', alpha=0.5)
        
        return []
    
    def run(self):
        """Display the plot."""
        plt.show()

if __name__ == '__main__':
    radar = RadarDisplay(com_port='COM3', baud_rate=9600)
    radar.run()