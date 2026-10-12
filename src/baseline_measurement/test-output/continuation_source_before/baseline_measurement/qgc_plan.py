"""Export the baseline route as a QGroundControl Plan file for inspection."""

import math


def make_plan(home, ref_lat, ref_lon, ref_alt):
    """Convert local NED home and route offsets using a spherical earth model."""
    if not all(math.isfinite(value) for value in (*home, ref_lat, ref_lon, ref_alt)):
        raise ValueError('Plan requires finite home and global reference')
    if not -90. < ref_lat < 90. or not -180. <= ref_lon <= 180.:
        raise ValueError('Invalid global reference')
    radius = 6378137.
    latitude = ref_lat + math.degrees(home[0] / radius)
    longitude = ref_lon + math.degrees(home[1] / (radius * math.cos(math.radians(ref_lat))))
    home_alt = ref_alt - home[2]
    items = []
    offsets = ((0., 0.), (20., 0.), (20., 20.), (0., 20.), (0., 0.), (0., 0.))
    for index, (north, east) in enumerate(offsets):
        lat = latitude + math.degrees(north / radius)
        lon = longitude + math.degrees(east / (radius * math.cos(math.radians(latitude))))
        command = 22 if index == 0 else (21 if index == 5 else 16)
        altitude = 0. if command == 21 else 10.
        items.append({'type': 'SimpleItem', 'autoContinue': True, 'command': command,
                      'frame': 3, 'doJumpId': index + 1, 'Altitude': altitude,
                      'AltitudeMode': 1, 'AMSLAltAboveTerrain': None,
                      'params': [0., 0., 0., None, lat, lon, altitude]})
    return {'fileType': 'Plan', 'groundStation': 'QGroundControl', 'version': 1,
            'geoFence': {'circles': [], 'polygons': [], 'version': 2},
            'rallyPoints': {'points': [], 'version': 2},
            'mission': {'version': 2, 'firmwareType': 12, 'vehicleType': 2,
                        'cruiseSpeed': 2., 'hoverSpeed': 2.,
                        'plannedHomePosition': [latitude, longitude, home_alt],
                        'items': items}}
