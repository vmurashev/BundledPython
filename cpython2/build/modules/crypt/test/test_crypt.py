from test import test_support
import unittest

crypt = test_support.import_module('crypt')

class CryptTestCase(unittest.TestCase):

    def test_crypt(self):
        cr = crypt.crypt('mypassword', 'ab')
        cr2 = crypt.crypt('mypassword', cr[0:2])
        self.assertEqual(cr2, cr)

def test_main():
    test_support.run_unittest(CryptTestCase)

if __name__ == "__main__":
    test_main()
