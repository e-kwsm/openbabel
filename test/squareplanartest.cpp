#include "obtest.h"
#include <iostream>
#include <openbabel/mol.h>
#include <openbabel/stereo/squareplanar.h>

using namespace std;
using namespace OpenBabel;

void testGetType ()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  EXPECT_TRUE( sp.GetType() == OBStereo::SquarePlanar );
}

void testCenter()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  OBSquarePlanarStereo::Config cfg;
  cfg.center = 42;
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);
  sp.SetConfig(cfg);
  ASSERT_TRUE( sp.GetConfig().center == 42 );
}

void testIsValid()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  OBSquarePlanarStereo::Config cfg;
  
  ASSERT_TRUE( !sp.IsValid() );
  // set center atom
  cfg.center = 5;
  cout << "This error can be ignored" << endl;
  sp.SetConfig(cfg);
  ASSERT_TRUE( !sp.IsValid() );
  // set reference atoms
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);
  sp.SetConfig(cfg);
  // the object should now be valid
  ASSERT_TRUE( sp.IsValid() );
}

// test basic ref setting/getting
void testRefs1()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  OBSquarePlanarStereo::Config cfg;

  // 1   4     1   4     1   4     1   4
  //  \ /      |   |     |  /|      \ /
  //   C    =  | C |  =  | C |  =    C
  //  / \      |   |     |/  |      / \
  // 2   3     2---3     2   3     2---3

  // set refs using default U shape
  cfg.center = 0;
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);
  sp.SetConfig(cfg);

  vector<unsigned long> refs;
  // get refs using default U shape
  refs = sp.GetConfig().refs;
  ASSERT_TRUE( refs.size() == 4 );
  ASSERT_TRUE( refs[0] == 1 );
  ASSERT_TRUE( refs[1] == 2 );
  ASSERT_TRUE( refs[2] == 3 );
  ASSERT_TRUE( refs[3] == 4 );

  // get refs using Z shape
  refs = sp.GetConfig(OBStereo::ShapeZ).refs;
  ASSERT_TRUE( refs.size() == 4 );
  ASSERT_TRUE( refs[0] == 1 );
  ASSERT_TRUE( refs[1] == 2 );
  ASSERT_TRUE( refs[2] == 4 );
  ASSERT_TRUE( refs[3] == 3 );

  // get refs using 4 shape
  refs = sp.GetConfig(OBStereo::Shape4).refs;
  ASSERT_TRUE( refs.size() == 4 );
  ASSERT_TRUE( refs[0] == 1 );
  ASSERT_TRUE( refs[1] == 3 );
  ASSERT_TRUE( refs[2] == 2 );
  ASSERT_TRUE( refs[3] == 4 );
}
 
void testRefs2()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  OBSquarePlanarStereo::Config cfg;

  // 1   4     1   4     1   4     1   4
  //  \ /      |   |     |  /|      \ /
  //   C    =  | C |  =  | C |  =    C
  //  / \      |   |     |/  |      / \
  // 2   3     2---3     2   3     2---3

  // set refs using default U shape
  cfg.center = 0;
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);
  sp.SetConfig(cfg);

  vector<unsigned long> refs;
  // get refs using default U shape starting from 1
  refs = sp.GetConfig((unsigned long)1).refs;
  ASSERT_TRUE( refs.size() == 4 );
  ASSERT_TRUE( refs[0] == 1 );
  ASSERT_TRUE( refs[1] == 2 );
  ASSERT_TRUE( refs[2] == 3 );
  ASSERT_TRUE( refs[3] == 4 );

  // get refs using Z shape
  refs = sp.GetConfig(OBStereo::ShapeZ).refs;
  ASSERT_TRUE( refs.size() == 4 );
  ASSERT_TRUE( refs[0] == 1 );
  ASSERT_TRUE( refs[1] == 2 );
  ASSERT_TRUE( refs[2] == 4 );
  ASSERT_TRUE( refs[3] == 3 );

  // get refs using 4 shape
  refs = sp.GetConfig(OBStereo::Shape4).refs;
  ASSERT_TRUE( refs.size() == 4 );
  ASSERT_TRUE( refs[0] == 1 );
  ASSERT_TRUE( refs[1] == 3 );
  ASSERT_TRUE( refs[2] == 2 );
  ASSERT_TRUE( refs[3] == 4 );

}
  
void testSquarePlanar()
{
  OBMol mol;
  OBSquarePlanarStereo sp(&mol);
  OBSquarePlanarStereo::Config cfg;
  cfg.center = 0;
  // set refs using default U shape
  cfg.refs =  OBStereo::MakeRefs(1, 2, 3, 4);
  sp.SetConfig(cfg);

  //
  // Trans
  //

  // test invalid ids
  ASSERT_TRUE( !sp.IsTrans(43, 3) );
  ASSERT_TRUE( !sp.IsTrans(1, 1) );
  
  // test real trans refs in all combinations
  ASSERT_TRUE( sp.IsTrans(1, 3) );
  ASSERT_TRUE( sp.IsTrans(3, 1) );
  ASSERT_TRUE( sp.IsTrans(2, 4) );
  ASSERT_TRUE( sp.IsTrans(4, 2) );

  // test cis atoms, should not be trans...
  ASSERT_TRUE( !sp.IsTrans(1, 2) );
  ASSERT_TRUE( !sp.IsTrans(1, 4) );
  ASSERT_TRUE( !sp.IsTrans(2, 1) );
  ASSERT_TRUE( !sp.IsTrans(2, 3) );
  ASSERT_TRUE( !sp.IsTrans(3, 2) );
  ASSERT_TRUE( !sp.IsTrans(3, 4) );
  ASSERT_TRUE( !sp.IsTrans(4, 1) );
  ASSERT_TRUE( !sp.IsTrans(4, 3) );

  // 
  // Cis
  //

  // test invalid ids
  ASSERT_TRUE( !sp.IsCis(43, 3) );
  ASSERT_TRUE( !sp.IsCis(1, 1) );
  
  // test real cis refs in all combinations
  ASSERT_TRUE( sp.IsCis(1, 2) );
  ASSERT_TRUE( sp.IsCis(2, 1) );
  ASSERT_TRUE( sp.IsCis(1, 4) );
  ASSERT_TRUE( sp.IsCis(4, 1) );

  ASSERT_TRUE( sp.IsCis(2, 1) );
  ASSERT_TRUE( sp.IsCis(2, 3) );
  ASSERT_TRUE( sp.IsCis(3, 2) );
  ASSERT_TRUE( sp.IsCis(3, 4) );
  ASSERT_TRUE( sp.IsCis(4, 3) );
  ASSERT_TRUE( sp.IsCis(4, 1) );

  // test trans atoms, should not be cis...
  ASSERT_TRUE( !sp.IsCis(1, 3) );
  ASSERT_TRUE( !sp.IsCis(2, 4) );

  // test GetTransRef 
  ASSERT_TRUE( sp.GetTransRef(1) == 3);
  ASSERT_TRUE( sp.GetTransRef(3) == 1);
  ASSERT_TRUE( sp.GetTransRef(2) == 4);
  ASSERT_TRUE( sp.GetTransRef(4) == 2);
   // test GetCisRef 
  vector<unsigned long> cis = sp.GetCisRefs(1);
  ASSERT_TRUE( cis.size() == 2 );
  ASSERT_TRUE( cis[0] == 2 || cis[1] == 2);
  ASSERT_TRUE( cis[0] == 4 || cis[1] == 4);
  cis = sp.GetCisRefs(4);
  ASSERT_TRUE( cis.size() == 2 );
  ASSERT_TRUE( cis[0] == 1 || cis[1] == 1);
  ASSERT_TRUE( cis[0] == 3 || cis[1] == 3);
  cis = sp.GetCisRefs(2);
  ASSERT_TRUE( cis.size() == 2 );
  ASSERT_TRUE( cis[0] == 1 || cis[1] == 1);
  ASSERT_TRUE( cis[0] == 3 || cis[1] == 3);
 
}

void test_equalsThisOperator()
{
  OBSquarePlanarStereo sq1(nullptr), sq2(nullptr);
  OBSquarePlanarStereo::Config cfg;
  cfg.center = 0;
  cfg.refs = OBStereo::MakeRefs(1, 2, 3, 4);

  sq1.SetConfig(cfg);
  sq2.SetConfig(cfg);
  EXPECT_TRUE( sq1 == sq2 );

  cfg.shape = OBStereo::ShapeZ;
  sq2.SetConfig(cfg);
  EXPECT_TRUE( sq1 != sq2 );

  OBStereo::Permutate(cfg.refs, 0, 1);
  sq2.SetConfig(cfg);
  EXPECT_TRUE( sq1 == sq2 );
}

int squareplanartest(int argc, char* argv[])
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
    testGetType();
    break;
  case 2:
    testCenter();
    break;
  case 3:
    testIsValid();
    break;
  case 4:
    testRefs1();
    testRefs2();
    break;
  case 5:
    testSquarePlanar();
    test_equalsThisOperator();
    break;
  default:
    cout << "Test number " << choice << " does not exist!\n";
    return -1;
  }

  
  cout << "end" << endl;

  return 0;
}

                
