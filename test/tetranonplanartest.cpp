#include "obtest.h"
#include <openbabel/stereo/tetrahedral.h>

using namespace std;
using namespace OpenBabel;

bool hasSameWinding(const OBStereo::Refs &refs1, const OBStereo::Refs &refs2)
{
  ASSERT_TRUE( refs1.size() == 3 );
  ASSERT_TRUE( refs2.size() == 3 );

  int Ni1 = OBStereo::NumInversions(refs1);
  int Ni2 = OBStereo::NumInversions(refs2);

  return ((Ni1 + Ni2) % 2 == 0);
}

//        2    3
//        -  ///
//        - //
//  0 --- 1
//         \
//          \
//           4


int tetranonplanartest(int /*argc*/, char* /*argv*/[])
{
  OBTetrahedralStereo::Config cfg;

  // set clockwise, viewing from 1
  cfg.from = 0;
  cfg.center = 1;
  cfg.refs = OBStereo::MakeRefs(2, 3, 4);
  ASSERT_TRUE( cfg.from == 0 );
  ASSERT_TRUE( cfg.center == 1 );
  ASSERT_TRUE( cfg.refs.size() == 3 );
  ASSERT_TRUE( cfg.refs[0] == 2 );
  ASSERT_TRUE( cfg.refs[1] == 3 );
  ASSERT_TRUE( cfg.refs[2] == 4 );

  // test nothing operation
  OBTetrahedralStereo::Config cfg2;
  cfg2 = OBTetraNonPlanarStereo::ToConfig(cfg, 0);
  EXPECT_TRUE( cfg == cfg2 );
  
  OBTetrahedralStereo::Config cfg3;
  // try viewing from other atom: 2
  cfg2 = OBTetraNonPlanarStereo::ToConfig(cfg, 2);
  EXPECT_TRUE( cfg2.center == 1 );
  EXPECT_TRUE( cfg2.from == 2 );
  EXPECT_TRUE( cfg2.refs.size() == 3 );
  EXPECT_TRUE( hasSameWinding(cfg2.refs, OBStereo::MakeRefs(3, 0, 4)) );
 
  // try viewing from other atom: 3
  cfg2 = OBTetraNonPlanarStereo::ToConfig(cfg, 3);
  EXPECT_TRUE( cfg2.center == 1 );
  EXPECT_TRUE( cfg2.from == 3 );
  EXPECT_TRUE( cfg2.refs.size() == 3 );
  EXPECT_TRUE( hasSameWinding(cfg2.refs, OBStereo::MakeRefs(0, 2, 4)) );
 
  // try viewing from other atom: 4
  cfg2 = OBTetraNonPlanarStereo::ToConfig(cfg, 4);
  EXPECT_TRUE( cfg2.center == 1 );
  EXPECT_TRUE( cfg2.from == 4 );
  EXPECT_TRUE( cfg2.refs.size() == 3 );
  EXPECT_TRUE( hasSameWinding(cfg2.refs, OBStereo::MakeRefs(3, 2, 0)) );

  // try viewing anti-clockwise 
  cfg2 = OBTetraNonPlanarStereo::ToConfig(cfg, 3, OBStereo::AntiClockwise);
  EXPECT_TRUE( cfg2.center == 1 );
  EXPECT_TRUE( cfg2.towards == 3 );
  EXPECT_TRUE( cfg2.refs.size() == 3 );
  EXPECT_TRUE( hasSameWinding(cfg2.refs, OBStereo::MakeRefs(2, 0, 4)) ); // CW <-> ACW = inversion

  // try viewing towards atom
  cfg2 = OBTetraNonPlanarStereo::ToConfig(cfg, 3, OBStereo::Clockwise, OBStereo::ViewTowards);
  EXPECT_TRUE( cfg2.center == 1 );
  EXPECT_TRUE( cfg2.towards == 3 );
  EXPECT_TRUE( cfg2.refs.size() == 3 );
  EXPECT_TRUE( hasSameWinding(cfg2.refs, OBStereo::MakeRefs(2, 0, 4)) ); // from <-> towards = inversion
 
  // try viewing towards atom anti-clockwise
  cfg2 = OBTetraNonPlanarStereo::ToConfig(cfg, 3, OBStereo::AntiClockwise, OBStereo::ViewTowards);
  EXPECT_TRUE( cfg2.center == 1 );
  EXPECT_TRUE( cfg2.towards == 3 );
  EXPECT_TRUE( cfg2.refs.size() == 3 );
  EXPECT_TRUE( hasSameWinding(cfg2.refs, OBStereo::MakeRefs(0, 2, 4)) ); // 2 permutations cancel out

  return 0;
}
