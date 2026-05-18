r"""Example test that uses the OpenBabel Python bindings

On Windows or Linux, you can run these tests at the commandline
in the build folder with:
"C:\Program Files\CMake 2.6\bin\ctest.exe" -C CTestTestfile.cmake
                                           -R pybindtest -VV

You could also "chdir" into build/test and run the test file directly:
python ../../test/testexample.py

In both cases, the test file is run directly from the source folder,
and so you can quickly develop the tests and try them out.
"""

import unittest
from openbabel import pybel
from testbindings import PybelWrapper


class ExamplePybelTest(PybelWrapper):

    def testNumberOfAtoms(self):
        mol = pybel.readstring("smi", "C(=O)Cl")
        mol.addh()
        self.assertEqual(mol.OBMol.NumAtoms(), 4)


if __name__ == "__main__":
    unittest.main()
