"""Check that the exported Plan preserves baseline geometry and NED signs."""

import json
import math
import unittest

from baseline_measurement.qgc_plan import make_plan


class PlanTests(unittest.TestCase):
    def test_route_altitudes_home_and_commands(self):
        plan = make_plan((3., 4., -.2), 47., 8., 488.)
        json.dumps(plan, allow_nan=False)
        mission = plan['mission']
        self.assertAlmostEqual(mission['plannedHomePosition'][2], 488.2)
        items = mission['items']
        self.assertEqual([item['command'] for item in items], [22, 16, 16, 16, 16, 21])
        self.assertEqual([item['params'][6] for item in items], [10.] * 5 + [0.])
        first, north, east = [item['params'][4:6] for item in items[:3]]
        self.assertGreater(north[0], first[0])
        self.assertAlmostEqual(north[1], first[1])
        self.assertAlmostEqual(east[0], north[0])
        self.assertGreater(east[1], north[1])
        self.assertEqual(items[4]['params'][4:6], first)
        self.assertTrue(all(item['params'][3] is None for item in items))

    def test_invalid_reference_is_rejected(self):
        for lat, lon, alt in [(math.nan, 8., 488.), (90., 8., 488.), (47., 181., 488.)]:
            with self.assertRaises(ValueError):
                make_plan((0., 0., 0.), lat, lon, alt)
