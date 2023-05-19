from rplidar import RPLidar
import numpy as np
import matplotlib.pyplot as plt

import matplotlib
import matplotlib.patches as patches
import json

lidar = RPLidar('/dev/ttyUSB0') # ls /dev/tty.*

points_cartesian = []
points_polar = []

collect = False

def on_close(arg):
    lidar.stop()
    lidar.stop_motor()
    lidar.disconnect()
    plt.close('all')

    if collect:
        with open("./points_cartesian.json", "w") as pc:
            json.dump(points_cartesian, pc)

        with open("./points_polar.json", "w") as pp:
            json.dump(points_polar, pp)

        exit()


def lidar_scan():
    #info = lidar.get_info()
    #print(info)

    #health = lidar.get_health()
    #print(health)

    '''fig, ax = plt.subplots()

    plot_size = 10
    plot_size = plot_size*1000'''

    for scan in lidar.iter_scans():
       
        np_scan = np.array(scan)
        # Extract the angle, distance, and quality values
        angles = np.radians(np_scan[:, 1])
        distances = np_scan[:, 2]
        qualities = np_scan[:, 0]

        # Convert the polar coordinates to Cartesian coordinates
        x = distances * np.cos(angles)
        y = distances * np.sin(angles)

        print(x, y)

        points_cartesian.append([x.tolist(), y.tolist()])
        points_polar.append([angles.tolist(), distances.tolist()])
        
        # Plot the LiDAR data
        '''ax.clear()
        ax.set_xlim([-plot_size, plot_size])
        ax.set_ylim([-plot_size, plot_size])

        ax.scatter(x, y, c=qualities, cmap='coolwarm', vmin=0, vmax=255, alpha=0.7)
        ax.scatter(0, 0, c='red', alpha=1)

        # Add the circle patch
        circle2 = patches.Circle((0, 0), radius=2000, edgecolor='r', facecolor='none', alpha=0.3)
        circle4 = patches.Circle((0, 0), radius=4000, edgecolor='r', facecolor='none', alpha=0.3)
        circle6 = patches.Circle((0, 0), radius=6000, edgecolor='r', facecolor='none', alpha=0.3)
        circle8 = patches.Circle((0, 0), radius=8000, edgecolor='r', facecolor='none', alpha=0.3)
        ax.add_patch(circle2)
        ax.add_patch(circle4)
        ax.add_patch(circle6)
        ax.add_patch(circle8)

        # Set the axis labels and plot title
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_title('LiDAR Data')

        # Update the plot
        plt.pause(0.00001)

        fig.canvas.mpl_connect('close_event', on_close)'''

    lidar.stop()
    #lidar.start_motor()
    lidar.stop_motor()
    lidar.disconnect()


if __name__ == "__main__":
    collect = True
    lidar_scan()