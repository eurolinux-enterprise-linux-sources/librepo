import unittest
import librepo

class TestCaseVersion(unittest.TestCase):
    def test_version(self):
        self.assertTrue(len(librepo.VERSION) >= 5)
        self.assertEqual(librepo.VERSION.count('.'), 2)
