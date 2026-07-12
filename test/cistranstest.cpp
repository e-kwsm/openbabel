#include "obtest.h"

#include <iostream>

#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/stereo/cistrans.h>
#include <openbabel/elements.h>
#include <openbabel/atom.h>

using namespace std;
using namespace OpenBabel;

void test_GetType ()
{
  OBMol mol;
  OBCisTransStereo ct(&mol);
  EXPECT_TRUE( ct.GetType() == OBStereo::CisTrans );
}

void test_configStruct()
{
  // reference Config
  OBCisTransStereo::Config reference(0, 1, OBStereo::MakeRefs(2, 3, 4, 5), OBStereo::ShapeU);
  
  EXPECT_TRUE( reference.begin == 0 );
  EXPECT_TRUE( reference.end == 1 );
  EXPECT_TRUE( reference.refs.size() == 4 );
  EXPECT_TRUE( reference.shape == OBStereo::ShapeU );

  // test copying
  OBCisTransStereo::Config referenceCopy = reference;
  EXPECT_TRUE( reference == referenceCopy );

  // invalid begin id
  OBCisTransStereo::Config invalidBegin(45, 1, OBStereo::MakeRefs(2, 3, 4, 5), OBStereo::ShapeU);
  EXPECT_TRUE( reference != invalidBegin );

  // invalid end id
  OBCisTransStereo::Config invalidEnd(0, 45, OBStereo::MakeRefs(2, 3, 4, 5), OBStereo::ShapeU);
  EXPECT_TRUE( reference != invalidEnd );

  // test other refs
  OBCisTransStereo::Config cfg1(0, 1, OBStereo::MakeRefs(2, 4, 3, 5), OBStereo::ShapeU);
  EXPECT_TRUE( reference != cfg1 );

  // test Z shape == U shape
  OBCisTransStereo::Config cfg2(0, 1, OBStereo::MakeRefs(3, 2, 4, 5), OBStereo::ShapeZ);
  EXPECT_TRUE( reference == cfg2 );

  // test 4 shape == U shape
  OBCisTransStereo::Config cfg3(0, 1, OBStereo::MakeRefs(2, 4, 3, 5), OBStereo::Shape4);
  EXPECT_TRUE( reference == cfg3 );

  // test Z shape == U shape
  EXPECT_TRUE( cfg2 == cfg3 );

}

void test_IsValid()
{
  OBMol mol;
  OBCisTransStereo ct(&mol);
  OBCisTransStereo::Config cfg, cfgCopy;
  cfg.begin = 0;
  cfg.end = 1;
  cfg.refs = OBStereo::MakeRefs(2, 3, 4, 5);

  ct.SetConfig(cfg);
  EXPECT_TRUE( ct.IsValid() );

  // no begin
  cfgCopy = cfg;
  cfgCopy.begin = OBStereo::NoRef;
  ct.SetConfig(cfgCopy);
  EXPECT_TRUE( !ct.IsValid() );

  // no end
  cfgCopy = cfg;
  cfgCopy.end = OBStereo::NoRef;
  ct.SetConfig(cfgCopy);
  EXPECT_TRUE( !ct.IsValid() );

  // no refs
  cfgCopy = cfg;
  cfgCopy.refs = std::vector<unsigned long>();
  ct.SetConfig(cfgCopy);
  EXPECT_TRUE( !ct.IsValid() );
}

void test_equalsOperator()
{
  OBCisTransStereo ct1(nullptr), ct2(nullptr);
  OBCisTransStereo::Config cfg;
  cfg.begin = 0;
  cfg.end = 1;
  cfg.refs = OBStereo::MakeRefs(2, 3, 4, 5);

  ct1.SetConfig(cfg);
  ct2.SetConfig(cfg);
  EXPECT_TRUE( ct1 == ct2 );

  cfg.shape = OBStereo::ShapeZ;
  ct2.SetConfig(cfg);
  EXPECT_TRUE( ct1 != ct2 );

  OBStereo::Permutate(cfg.refs, 0, 1);
  ct2.SetConfig(cfg);
  EXPECT_TRUE( ct1 == ct2 );
}

void test_GetSetConfig()
{
  OBCisTransStereo ct(nullptr);
  OBCisTransStereo::Config cfg;

  // set clockwise, viewing from 1
  EXPECT_TRUE( !ct.IsValid() );
  cfg.refs = OBStereo::MakeRefs(2, 3, 4, 5);
  cfg.begin = 0;
  cfg.end = 1;
  ct.SetConfig(cfg);
  EXPECT_TRUE( ct.IsValid() );

  OBCisTransStereo::Config cfg2 = ct.GetConfig();
  EXPECT_TRUE( cfg2.begin == 0 );
  EXPECT_TRUE( cfg2.end == 1 );
  EXPECT_TRUE( cfg2.refs.size() == 4 );
  EXPECT_TRUE( cfg2.refs[0] == 2 );
  EXPECT_TRUE( cfg2.refs[1] == 3 );
  EXPECT_TRUE( cfg2.refs[2] == 4 );
  EXPECT_TRUE( cfg2.refs[3] == 5 );
  EXPECT_TRUE( cfg2.shape == OBStereo::ShapeU );
  EXPECT_TRUE( cfg == cfg2 );

}

void testRefs()
{
  OBMol mol;
  OBCisTransStereo ct(&mol);

  // 1   4     1   4     1---4     1   4
  //  \ /      |   |        /       \ /
  //   C    =  | C |  =    C    =    C
  //  / \      |   |      /         / \
  // 2   3     2---3     2---3     2---3

  // set refs using default U shape
  OBCisTransStereo::Config cfg(0, 1, OBStereo::MakeRefs(2, 3, 4, 5));
  ct.SetConfig(cfg);

  // get config using Z shape
  OBCisTransStereo::Config cfg2 = ct.GetConfig(OBStereo::ShapeZ);
  EXPECT_TRUE( cfg2.refs.size() == 4 );
  EXPECT_TRUE( cfg2.refs[0] == 2 );
  EXPECT_TRUE( cfg2.refs[1] == 3 );
  EXPECT_TRUE( cfg2.refs[2] == 5 );
  EXPECT_TRUE( cfg2.refs[3] == 4 );

  // get config using 4 shape
  cfg2 = ct.GetConfig(OBStereo::Shape4);
  EXPECT_TRUE( cfg2.refs.size() == 4 );
  EXPECT_TRUE( cfg2.refs[0] == 2 );
  EXPECT_TRUE( cfg2.refs[1] == 4 );
  EXPECT_TRUE( cfg2.refs[2] == 3 );
  EXPECT_TRUE( cfg2.refs[3] == 5 );
}
  
void test_IsOnSameAtom1()
{
  OBConversion conv;
  conv.SetInFormat("smi");
  OBMol mol;
  //
  // C       I     C      I    0      5
  //  \     /      |      |    |      |
  //   C===C       | C  C |    | 1  3 |
  //  /     \      |      |    |      |
  // Cl      F     Cl-----F    2------4
  //
  EXPECT_TRUE( conv.ReadString(&mol, "CC(Cl)=C(F)I") );
  EXPECT_TRUE( mol.NumAtoms() == 6 );
  
  EXPECT_TRUE( mol.GetAtomById(1) );
  EXPECT_TRUE( mol.GetAtomById(1)->GetAtomicNum() == OBElements::Carbon );
  EXPECT_TRUE( mol.GetAtomById(1)->GetExplicitDegree() == 3);
  EXPECT_TRUE( mol.GetAtomById(3) );
  EXPECT_TRUE( mol.GetAtomById(3)->GetAtomicNum() == OBElements::Carbon );
  EXPECT_TRUE( mol.GetAtomById(3)->GetExplicitDegree() == 3);

  EXPECT_TRUE( mol.GetAtomById(4) );
  EXPECT_TRUE( mol.GetAtomById(4)->GetAtomicNum() == 9 );
  EXPECT_TRUE( mol.GetAtomById(5) );
  EXPECT_TRUE( mol.GetAtomById(5)->GetAtomicNum() == 53 );

  OBCisTransStereo ct(&mol);
  // set refs using default U shape
  ct.SetConfig(OBCisTransStereo::Config(1, 3, OBStereo::MakeRefs(0, 2, 4, 5)));

  EXPECT_TRUE( ct.IsOnSameAtom(0, 2) );
  EXPECT_TRUE( ct.IsOnSameAtom(2, 0) );
  EXPECT_TRUE( ct.IsOnSameAtom(4, 5) );
  EXPECT_TRUE( ct.IsOnSameAtom(5, 4) );
  
  EXPECT_TRUE( !ct.IsOnSameAtom(0, 5) );
  EXPECT_TRUE( !ct.IsOnSameAtom(5, 0) );
  EXPECT_TRUE( !ct.IsOnSameAtom(0, 4) );
  EXPECT_TRUE( !ct.IsOnSameAtom(4, 0) );
 
  EXPECT_TRUE( !ct.IsOnSameAtom(2, 5) );
  EXPECT_TRUE( !ct.IsOnSameAtom(5, 2) );
  EXPECT_TRUE( !ct.IsOnSameAtom(2, 4) );
  EXPECT_TRUE( !ct.IsOnSameAtom(4, 2) );
  
}

void test_IsOnSameAtom2()
{
  obErrorLog.SetOutputLevel(obInfo);
  OBConversion conv;
  conv.SetInFormat("smi");
  OBMol mol;
  //
  //  Br      I     C      I    0      5
  //   \     /      |      |    |      |
  //    C===C       | C  C |    | 1  3 |
  //   /     \      |      |    |      |
  //  Cl      F     Cl-----F    2------4
  //
  EXPECT_TRUE( conv.ReadString(&mol, "[Br]C([Cl])=C(F)I") );
  EXPECT_TRUE( mol.NumAtoms() == 6 );
  
  OBCisTransStereo ct(&mol);
  // set refs using default U shape
  ct.SetConfig(OBCisTransStereo::Config(1, 3, OBStereo::MakeRefs(0, 2, 4, 5)));
  
  EXPECT_TRUE( ct.IsOnSameAtom(0, 2) );
  EXPECT_TRUE( ct.IsOnSameAtom(2, 0) );
  EXPECT_TRUE( ct.IsOnSameAtom(4, 5) );
  EXPECT_TRUE( ct.IsOnSameAtom(5, 4) );
  EXPECT_TRUE( !ct.IsOnSameAtom(0, 5) );
  EXPECT_TRUE( !ct.IsOnSameAtom(5, 0) );
  EXPECT_TRUE( !ct.IsOnSameAtom(0, 4) );
  EXPECT_TRUE( !ct.IsOnSameAtom(4, 0) );

  //
  // Trans
  //

  EXPECT_TRUE( ct.GetTransRef(0) == 4 );
  EXPECT_TRUE( ct.GetTransRef(4) == 0 );
  EXPECT_TRUE( ct.GetTransRef(2) == 5 );
  EXPECT_TRUE( ct.GetTransRef(5) == 2 );

  EXPECT_TRUE( ct.GetTransRef(0) != 2 );
  EXPECT_TRUE( ct.GetTransRef(2) != 0 );
  EXPECT_TRUE( ct.GetTransRef(4) != 5 );
  EXPECT_TRUE( ct.GetTransRef(5) != 4 );
  
  EXPECT_TRUE( ct.IsTrans(0, 4) );
  EXPECT_TRUE( ct.IsTrans(2, 5) );
  EXPECT_TRUE( !ct.IsTrans(0, 2) );
  EXPECT_TRUE( !ct.IsTrans(0, 5) );

  //
  // Cis
  //

  EXPECT_TRUE( ct.GetCisRef(0) == 5 );
  EXPECT_TRUE( ct.GetCisRef(5) == 0 );
  EXPECT_TRUE( ct.GetCisRef(2) == 4 );
  EXPECT_TRUE( ct.GetCisRef(4) == 2 );

  EXPECT_TRUE( ct.GetCisRef(2) != 5 );
  EXPECT_TRUE( ct.GetCisRef(5) != 2 );
  EXPECT_TRUE( ct.GetCisRef(0) != 4 );
  EXPECT_TRUE( ct.GetCisRef(4) != 0 );
  
  EXPECT_TRUE( ct.IsCis(0, 5) );
  EXPECT_TRUE( ct.IsCis(2, 4) );
  EXPECT_TRUE( !ct.IsCis(0, 4) );
  EXPECT_TRUE( !ct.IsCis(2, 5) );

}

void test_CisTrans1()
{
  obErrorLog.SetOutputLevel(obInfo);
  OBConversion conv;
  conv.SetInFormat("smi");
  OBMol mol;
  // 
  //  F       F      F      F     0      3
  //   \     /       |      |     |      |
  //    C===C        | C  C |     | 1  2 |
  //   /     \       |      |     |      |
  // (H)     (H)    (H)----(H)    H------H
  //
  EXPECT_TRUE( conv.ReadString(&mol, "FC=CF") );
  OBCisTransStereo ct(&mol);
  ct.SetConfig(OBCisTransStereo::Config(1, 2, OBStereo::MakeRefs(0, 
      OBStereo::ImplicitRef, OBStereo::ImplicitRef, 3)));

  EXPECT_TRUE( ct.IsOnSameAtom(0, OBStereo::ImplicitRef) );
  EXPECT_TRUE( ct.IsOnSameAtom(3, OBStereo::ImplicitRef) );
  EXPECT_TRUE( !ct.IsOnSameAtom(OBStereo::ImplicitRef, OBStereo::ImplicitRef) );
  EXPECT_TRUE( !ct.IsOnSameAtom(0, 3) );

  EXPECT_TRUE( ct.GetCisRef(0) == 3 );
  EXPECT_TRUE( ct.GetCisRef(3) == 0 );
  
  EXPECT_TRUE( ct.GetTransRef(0) == OBStereo::ImplicitRef );
  EXPECT_TRUE( ct.GetTransRef(3) == OBStereo::ImplicitRef );
}

void test_CisTrans2()
{
  obErrorLog.SetOutputLevel(obInfo);
  OBConversion conv;
  conv.SetInFormat("smi");
  OBMol mol;
  // 
  //  F      (H)     F     (H)   0      H
  //   \     /       |      |    |      |
  //    C===C        | C  C |    | 1  2 |
  //   /     \       |      |    |      |
  // (H)      F     (H)-----F    H------3
  //
  EXPECT_TRUE( conv.ReadString(&mol, "FC=CF") );
  OBCisTransStereo ct(&mol);
  OBCisTransStereo::Config cfg(1, 2, OBStereo::MakeRefs(0, OBStereo::ImplicitRef, 3, OBStereo::ImplicitRef));
  ct.SetConfig(cfg);

  EXPECT_TRUE( ct.IsOnSameAtom(0, OBStereo::ImplicitRef) );
  EXPECT_TRUE( ct.IsOnSameAtom(3, OBStereo::ImplicitRef) );
  EXPECT_TRUE( !ct.IsOnSameAtom(OBStereo::ImplicitRef, OBStereo::ImplicitRef) );
  EXPECT_TRUE( !ct.IsOnSameAtom(0, 3) );

  EXPECT_TRUE( ct.GetTransRef(0) == 3 );
  EXPECT_TRUE( ct.GetTransRef(3) == 0 );
  
  EXPECT_TRUE( ct.GetCisRef(0) == OBStereo::ImplicitRef );
  EXPECT_TRUE( ct.GetCisRef(3) == OBStereo::ImplicitRef );
 

}

int cistranstest(int argc, char* argv[])
{
  int defaultchoice = 1;
  
  int choice = defaultchoice;

  if (argc > 1) {
    if(sscanf(argv[1], "%d", &choice) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
  }
  // Define location of file formats for testing
  #ifdef FORMATDIR
    char env[BUFF_SIZE];
    snprintf(env, BUFF_SIZE, "BABEL_LIBDIR=%s", FORMATDIR);
    putenv(env);
  #endif

  switch(choice) {
  case 1:
    test_GetType();
    break;
  case 2:
    test_configStruct();
    break;
  case 3:
    test_IsValid();
    break;
  case 4:
    test_equalsOperator();
    break;
  case 5:
    test_GetSetConfig();
    break;
  case 6:
    test_IsOnSameAtom1();
    break;
  case 7:
    test_IsOnSameAtom2();
    break;
  case 8:
    test_CisTrans1();
    break;
  case 9:
    test_CisTrans2();
    break;
  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }
  
  return 0;
}

                
