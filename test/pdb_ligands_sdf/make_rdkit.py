#!/usr/bin/env python3

from rdkit.Chem import AllChem as Chem

import sys,glob

rdkiterrors = 0
for fname in glob.glob('*.sdf'):
  try:
    mol = next(Chem.ForwardSDMolSupplier(fname))
    m = Chem.AddHs(mol,addCoords=True) 
    with open('rdkit_addh/%s'%fname,'wt') as o:
      o.write(Chem.MolToMolBlock(m))
  except KeyboardInterrupt:
    raise
  except:
    print(fname)
    rdkiterrors += 1

print('Total RDKit failures: %d'%rdkiterrors)
