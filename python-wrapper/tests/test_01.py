import unittest
import pytsa

class MyTestCase(unittest.TestCase):
    def test_something(self):
        data=pytsa.tsa.SeqView_double_t(0.0,0.1,1)
        self.assertEqual(data.GetStart(), 0.0)

if __name__ == '__main__':
    unittest.main()
