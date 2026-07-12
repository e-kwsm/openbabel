#include "obtest.h"
#include <openbabel/stereo/cistrans.h>

using namespace std;
using namespace OpenBabel;

//        2    3
//        -  ///
//        - //
//  0 --- 1
//         \
//          \
//           4


int tetraplanartest(int /*argc*/, char* /*argv*/[])
{
  OBCisTransStereo::Config cfg;

  // set clockwise, viewing from 1
  cfg.begin = 0;
  cfg.end = 1;
  cfg.refs = OBStereo::MakeRefs(2, 3, 4, 5);
  ASSERT_TRUE( cfg.begin == 0 );
  ASSERT_TRUE( cfg.end == 1 );
  ASSERT_TRUE( cfg.refs.size() == 4 );
  ASSERT_TRUE( cfg.refs[0] == 2 );
  ASSERT_TRUE( cfg.refs[1] == 3 );
  ASSERT_TRUE( cfg.refs[2] == 4 );
  ASSERT_TRUE( cfg.refs[3] == 5 );
  ASSERT_TRUE( cfg.shape == OBStereo::ShapeU );

  // test nothing operation
  OBCisTransStereo::Config cfg2;
  cfg2 = OBTetraPlanarStereo::ToConfig(cfg, 2);
  EXPECT_TRUE( cfg == cfg2 );
  EXPECT_TRUE( cfg2.refs[0] == cfg.refs[0] );
  EXPECT_TRUE( cfg2.refs[1] == cfg.refs[1] );
  EXPECT_TRUE( cfg2.refs[2] == cfg.refs[2] );
  EXPECT_TRUE( cfg2.refs[3] == cfg.refs[3] );
  
  // try start = 3
  cfg2 = OBTetraPlanarStereo::ToConfig(cfg, 3);
  EXPECT_TRUE( cfg2.begin == 0 );
  EXPECT_TRUE( cfg2.end == 1 );
  EXPECT_TRUE( cfg2.refs.size() == 4 );
  EXPECT_TRUE( cfg2.refs[0] == 3 );
  EXPECT_TRUE( cfg2.refs[1] == 4 );
  EXPECT_TRUE( cfg2.refs[2] == 5 );
  EXPECT_TRUE( cfg2.refs[3] == 2 );
  EXPECT_TRUE( cfg2.shape == OBStereo::ShapeU );

  // try start = 5
  cfg2 = OBTetraPlanarStereo::ToConfig(cfg, 5);
  EXPECT_TRUE( cfg2.begin == 0 );
  EXPECT_TRUE( cfg2.end == 1 );
  EXPECT_TRUE( cfg2.refs.size() == 4 );
  EXPECT_TRUE( cfg2.refs[0] == 5 );
  EXPECT_TRUE( cfg2.refs[1] == 2 );
  EXPECT_TRUE( cfg2.refs[2] == 3 );
  EXPECT_TRUE( cfg2.refs[3] == 4 );
  EXPECT_TRUE( cfg2.shape == OBStereo::ShapeU );

  // try U -> Z
  OBCisTransStereo::Config shapeZ = OBTetraPlanarStereo::ToConfig(cfg, 2, OBStereo::ShapeZ);
  EXPECT_TRUE( shapeZ.begin == 0 );
  EXPECT_TRUE( shapeZ.end == 1 );
  EXPECT_TRUE( shapeZ.refs.size() == 4 );
  EXPECT_TRUE( shapeZ.refs[0] == 2 );
  EXPECT_TRUE( shapeZ.refs[1] == 3 );
  EXPECT_TRUE( shapeZ.refs[2] == 5 );
  EXPECT_TRUE( shapeZ.refs[3] == 4 );
  EXPECT_TRUE( shapeZ.shape == OBStereo::ShapeZ );

  // try U -> 4
  OBCisTransStereo::Config shape4 = OBTetraPlanarStereo::ToConfig(cfg, 2, OBStereo::Shape4);
  EXPECT_TRUE( shape4.begin == 0 );
  EXPECT_TRUE( shape4.end == 1 );
  EXPECT_TRUE( shape4.refs.size() == 4 );
  EXPECT_TRUE( shape4.refs[0] == 2 );
  EXPECT_TRUE( shape4.refs[1] == 4 );
  EXPECT_TRUE( shape4.refs[2] == 3 );
  EXPECT_TRUE( shape4.refs[3] == 5 );
  EXPECT_TRUE( shape4.shape == OBStereo::Shape4 );

  // try Z -> U
  OBCisTransStereo::Config shapeU = OBTetraPlanarStereo::ToConfig(shapeZ, 2, OBStereo::ShapeU);
  EXPECT_TRUE( shapeU.begin == 0 );
  EXPECT_TRUE( shapeU.end == 1 );
  EXPECT_TRUE( shapeU.refs.size() == 4 );
  EXPECT_TRUE( shapeU.refs[0] == 2 );
  EXPECT_TRUE( shapeU.refs[1] == 3 );
  EXPECT_TRUE( shapeU.refs[2] == 4 );
  EXPECT_TRUE( shapeU.refs[3] == 5 );
  EXPECT_TRUE( shapeU.shape == OBStereo::ShapeU );

  // try 4 -> U
  shapeU = OBTetraPlanarStereo::ToConfig(shape4, 2, OBStereo::ShapeU);
  EXPECT_TRUE( shapeU.begin == 0 );
  EXPECT_TRUE( shapeU.end == 1 );
  EXPECT_TRUE( shapeU.refs.size() == 4 );
  EXPECT_TRUE( shapeU.refs[0] == 2 );
  EXPECT_TRUE( shapeU.refs[1] == 3 );
  EXPECT_TRUE( shapeU.refs[2] == 4 );
  EXPECT_TRUE( shapeU.refs[3] == 5 );
  EXPECT_TRUE( shapeU.shape == OBStereo::ShapeU );

  return 0;
}
