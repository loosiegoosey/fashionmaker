/************************************************************************
 **
 **  @file
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   1 6, 2017
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2017 Valentina project
 **  <https://gitlab.com/smart-pattern/valentina> All Rights Reserved.
 **
 **  Valentina is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Valentina is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Valentina.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "measurements.h"
#include "vtranslatemeasurements.h"
#include "../vmisc/def.h"

// Keep synchronize all names with initialization in VTranslateVars class!!!!!
//measurements
// A
const QString height_M                    = QStringLiteral("height");                         // A01
const QString heightNeckBack_M            = QStringLiteral("height_neck_back");               // A02
const QString heightScapula_M             = QStringLiteral("height_scapula");                 // A03
const QString heightArmpit_M              = QStringLiteral("height_armpit");                  // A04
const QString heightWaistSide_M           = QStringLiteral("height_waist_side");              // A05
const QString heightHip_M                 = QStringLiteral("height_hip");                     // A06
const QString heightGlutealFold_M         = QStringLiteral("height_gluteal_fold");            // A07
const QString heightKnee_M                = QStringLiteral("height_knee");                    // A08
const QString heightCalf_M                = QStringLiteral("height_calf");                    // A09
const QString heightAnkleHigh_M           = QStringLiteral("height_ankle_high");              // A10
const QString heightAnkle_M               = QStringLiteral("height_ankle");                   // A11
const QString heightHighhip_M             = QStringLiteral("height_highhip");                 // A12
const QString heightWaistFront_M          = QStringLiteral("height_waist_front");             // A13
const QString heightBustpoint_M           = QStringLiteral("height_bustpoint");               // A14
const QString heightShoulderTip_M         = QStringLiteral("height_shoulder_tip");            // A15
const QString heightNeckFront_M           = QStringLiteral("height_neck_front");              // A16
const QString heightNeckSide_M            = QStringLiteral("height_neck_side");               // A17
const QString heightNeckBackToKnee_M      = QStringLiteral("height_neck_back_to_knee");       // A18
const QString heightWaistSideToKnee_M     = QStringLiteral("height_waist_side_to_knee");      // A19
const QString heightWaistSideToHip_M      = QStringLiteral("height_waist_side_to_hip");       // A20
const QString heightKneeToAnkle_M         = QStringLiteral("height_knee_to_ankle");           // A21
const QString heightNeckBackToWaistSide_M = QStringLiteral("height_neck_back_to_waist_side"); // A22
const QString heightWaistBack_M           = QStringLiteral("height_waist_back");              // A23
// B
const QString widthShoulder_M     = QStringLiteral("width_shoulder");       // B01
const QString widthBust_M         = QStringLiteral("width_bust");           // B02
const QString widthWaist_M        = QStringLiteral("width_waist");          // B03
const QString widthHip_M          = QStringLiteral("width_hip");            // B04
const QString widthAbdomenToHip_M = QStringLiteral("width_abdomen_to_hip"); // B05
// C
const QString indentNeckBack_M  = QStringLiteral("indent_neck_back");  // C01
const QString indentWaistBack_M = QStringLiteral("indent_waist_back"); // C02
const QString indentAnkleHigh_M = QStringLiteral("indent_ankle_high"); // C03
// D
const QString handPalmLength_M = QStringLiteral("hand_palm_length"); // D01
const QString handLength_M     = QStringLiteral("hand_length");      // D02
const QString handPalmWidth_M  = QStringLiteral("hand_palm_width");  // D03
const QString handPalmCirc_M   = QStringLiteral("hand_palm_circ");   // D04
const QString handCirc_M       = QStringLiteral("hand_circ");        // D05
// E
const QString footWidth_M      = QStringLiteral("foot_width");       // E01
const QString footLength_M     = QStringLiteral("foot_length");      // E02
const QString footCirc_M       = QStringLiteral("foot_circ");        // E03
const QString footInstepCirc_M = QStringLiteral("foot_instep_circ"); // E04
// F
const QString headCirc_M            = QStringLiteral("head_circ");	             // F01
const QString headLength_M          = QStringLiteral("head_length");             // F02
const QString headDepth_M           = QStringLiteral("head_depth");	             // F03
const QString headWidth_M           = QStringLiteral("head_width");	             // F04
const QString headCrownToNeckBack_M = QStringLiteral("head_crown_to_neck_back"); // F05
const QString headChinToNeckBack_M  = QStringLiteral("head_chin_to_neck_back");  // F06
// G
const QString neckMidCirc_M        = QStringLiteral("neck_mid_circ");          // G01
const QString neckCirc_M           = QStringLiteral("neck_circ");              // G02
const QString highbustCirc_M       = QStringLiteral("highbust_circ");          // G03
const QString bustCirc_M           = QStringLiteral("bust_circ");              // G04
const QString lowbustCirc_M        = QStringLiteral("lowbust_circ");           // G05
const QString ribCirc_M            = QStringLiteral("rib_circ");               // G06
const QString waistCirc_M          = QStringLiteral("waist_circ");             // G07
const QString highhipCirc_M        = QStringLiteral("highhip_circ");           // G08
const QString hipCirc_M            = QStringLiteral("hip_circ");               // G09
const QString neckArcF_M           = QStringLiteral("neck_arc_f");             // G10
const QString highbustArcF_M       = QStringLiteral("highbust_arc_f");         // G11

// size and bust_arc_f are synonyms
const QString size_M               = QStringLiteral("size");                   // G12
const QString bustArcF_M           = QStringLiteral("bust_arc_f");             // G12

const QString lowbustArcF_M        = QStringLiteral("lowbust_arc_f");          // G13
const QString ribArcF_M            = QStringLiteral("rib_arc_f");              // G14
const QString waistArcF_M          = QStringLiteral("waist_arc_f");            // G15
const QString highhipArcF_M        = QStringLiteral("highhip_arc_f");          // G16
const QString hipArcF_M            = QStringLiteral("hip_arc_f");              // G17
const QString neckArcHalfF_M       = QStringLiteral("neck_arc_half_f");        // G18
const QString highbustArcHalfF_M   = QStringLiteral("highbust_arc_half_f");    // G19
const QString bustArcHalfF_M       = QStringLiteral("bust_arc_half_f");        // G20
const QString lowbustArcHalfF_M    = QStringLiteral("lowbust_arc_half_f");     // G21
const QString ribArcHalfF_M        = QStringLiteral("rib_arc_half_f");         // G22
const QString waistArcHalfF_M      = QStringLiteral("waist_arc_half_f");       // G23
const QString highhipArcHalfF_M    = QStringLiteral("highhip_arc_half_f");     // G24
const QString hipArcHalfF_M        = QStringLiteral("hip_arc_half_f");         // G25
const QString neckArcB_M           = QStringLiteral("neck_arc_b");             // G26
const QString highbustArcB_M       = QStringLiteral("highbust_arc_b");         // G27
const QString bustArcB_M           = QStringLiteral("bust_arc_b");             // G28
const QString lowbustArcB_M        = QStringLiteral("lowbust_arc_b");          // G29
const QString ribArcB_M            = QStringLiteral("rib_arc_b");              // G30
const QString waistArcB_M          = QStringLiteral("waist_arc_b");            // G31
const QString highhipArcB_M        = QStringLiteral("highhip_arc_b");          // G32
const QString hipArcB_M            = QStringLiteral("hip_arc_b");              // G33
const QString neckArcHalfB_M       = QStringLiteral("neck_arc_half_b");        // G34
const QString highbustArcHalfB_M   = QStringLiteral("highbust_arc_half_b");    // G35
const QString bustArcHalfB_M       = QStringLiteral("bust_arc_half_b");        // G36
const QString lowbustArcHalfB_M    = QStringLiteral("lowbust_arc_half_b");     // G37
const QString ribArcHalfB_M        = QStringLiteral("rib_arc_half_b");         // G38
const QString waistArcHalfB_M      = QStringLiteral("waist_arc_half_b");       // G39
const QString highhipArcHalfB_M    = QStringLiteral("highhip_arc_half_b");     // G40
const QString hipArcHalfB_M        = QStringLiteral("hip_arc_half_b");         // G41
const QString hipWithAbdomenArcF_M = QStringLiteral("hip_with_abdomen_arc_f"); // G42
const QString bodyArmfoldCirc_M    = QStringLiteral("body_armfold_circ");      // G43
const QString bodyBustCirc_M       = QStringLiteral("body_bust_circ");         // G44
const QString bodyTorsoCirc_M      = QStringLiteral("body_torso_circ");        // G45
const QString hipCircWithAbdomen_M = QStringLiteral("hip_circ_with_abdomen");  // G46
// H
const QString neckFrontToWaistF_M             = QStringLiteral("neck_front_to_waist_f");             // H01
const QString neckFrontToWaistFlatF_M         = QStringLiteral("neck_front_to_waist_flat_f");        // H02
const QString armpitToWaistSide_M             = QStringLiteral("armpit_to_waist_side");              // H03
const QString shoulderTipToWaistSideF_M       = QStringLiteral("shoulder_tip_to_waist_side_f");      // H04
const QString neckSideToWaistF_M              = QStringLiteral("neck_side_to_waist_f");              // H05
const QString neckSideToWaistBustpointF_M     = QStringLiteral("neck_side_to_waist_bustpoint_f");    // H06
const QString neckFrontToHighbustF_M          = QStringLiteral("neck_front_to_highbust_f");          // H07
const QString highbustToWaistF_M              = QStringLiteral("highbust_to_waist_f");               // H08
const QString neckFrontToBustF_M              = QStringLiteral("neck_front_to_bust_f");              // H09
const QString bustToWaistF_M                  = QStringLiteral("bust_to_waist_f");                   // H10
const QString lowbustToWaistF_M               = QStringLiteral("lowbust_to_waist_f");                // H11
const QString ribToWaistSide_M                = QStringLiteral("rib_to_waist_side");                 // H12
const QString shoulderTipToArmfoldF_M         = QStringLiteral("shoulder_tip_to_armfold_f");         // H13
const QString neckSideToBustF_M               = QStringLiteral("neck_side_to_bust_f");               // H14
const QString neckSideToHighbustF_M           = QStringLiteral("neck_side_to_highbust_f");           // H15
const QString shoulderCenterToHighbustF_M     = QStringLiteral("shoulder_center_to_highbust_f");     // H16
const QString shoulderTipToWaistSideB_M       = QStringLiteral("shoulder_tip_to_waist_side_b");      // H17
const QString neckSideToWaistB_M              = QStringLiteral("neck_side_to_waist_b");              // H18
const QString neckBackToWaistB_M              = QStringLiteral("neck_back_to_waist_b");              // H19
const QString neckSideToWaistScapulaB_M       = QStringLiteral("neck_side_to_waist_scapula_b");      // H20
const QString neckBackToHighbustB_M           = QStringLiteral("neck_back_to_highbust_b");           // H21
const QString highbustToWaistB_M              = QStringLiteral("highbust_to_waist_b");               // H22
const QString neckBackToBustB_M               = QStringLiteral("neck_back_to_bust_b");               // H23
const QString bustToWaistB_M                  = QStringLiteral("bust_to_waist_b");                   // H24
const QString lowbustToWaistB_M               = QStringLiteral("lowbust_to_waist_b");                // H25
const QString shoulderTipToArmfoldB_M         = QStringLiteral("shoulder_tip_to_armfold_b");         // H26
const QString neckSideToBustB_M               = QStringLiteral("neck_side_to_bust_b");               // H27
const QString neckSideToHighbustB_M           = QStringLiteral("neck_side_to_highbust_b");           // H28
const QString shoulderCenterToHighbustB_M     = QStringLiteral("shoulder_center_to_highbust_b");     // H29
const QString waistToHighhipF_M               = QStringLiteral("waist_to_highhip_f");                // H30
const QString waistToHipF_M                   = QStringLiteral("waist_to_hip_f");                    // H31
const QString waistToHighhipSide_M            = QStringLiteral("waist_to_highhip_side");             // H32
const QString waistToHighhipB_M               = QStringLiteral("waist_to_highhip_b");                // H33
const QString waistToHipB_M                   = QStringLiteral("waist_to_hip_b");                    // H34
const QString waistToHipSide_M                = QStringLiteral("waist_to_hip_side");                 // H35
const QString shoulderSlopeNeckSideAngle_M    = QStringLiteral("shoulder_slope_neck_side_angle");    // H36
const QString shoulderSlopeNeckSideLength_M   = QStringLiteral("shoulder_slope_neck_side_length");   // H37
const QString shoulderSlopeNeckBackAngle_M    = QStringLiteral("shoulder_slope_neck_back_angle");    // H38
const QString shoulderSlopeNeckBackHeight_M   = QStringLiteral("shoulder_slope_neck_back_height");   // H39
const QString shoulderSlopeShoulderTipAngle_M = QStringLiteral("shoulder_slope_shoulder_tip_angle"); // H40
const QString neckBackToAcrossBack_M          = QStringLiteral("neck_back_to_across_back");          // H41
const QString acrossBackToWaistB_M            = QStringLiteral("across_back_to_waist_b");            // H42
// I
const QString shoulderLength_M                = QStringLiteral("shoulder_length");                     // I01
const QString shoulderTipToShoulderTipF_M     = QStringLiteral("shoulder_tip_to_shoulder_tip_f");      // I02
const QString acrossChestF_M                  = QStringLiteral("across_chest_f");                      // I03
const QString armfoldToArmfoldF_M             = QStringLiteral("armfold_to_armfold_f");                // I04
const QString shoulderTipToShoulderTipHalfF_M = QStringLiteral("shoulder_tip_to_shoulder_tip_half_f"); // I05
const QString acrossChestHalfF_M              = QStringLiteral("across_chest_half_f");                 // I06
const QString shoulderTipToShoulderTipB_M     = QStringLiteral("shoulder_tip_to_shoulder_tip_b");      // I07
const QString acrossBackB_M                   = QStringLiteral("across_back_b");                       // I08
const QString armfoldToArmfoldB_M             = QStringLiteral("armfold_to_armfold_b");                // I09
const QString shoulderTipToShoulderTipHalfB_M = QStringLiteral("shoulder_tip_to_shoulder_tip_half_b"); // I10
const QString acrossBackHalfB_M               = QStringLiteral("across_back_half_b");                  // I11
const QString neckFrontToShoulderTipF_M       = QStringLiteral("neck_front_to_shoulder_tip_f");        // I12
const QString neckBackToShoulderTipB_M        = QStringLiteral("neck_back_to_shoulder_tip_b");         // I13
const QString neckWidth_M                     = QStringLiteral("neck_width");                          // I14
// J
const QString bustpointToBustpoint_M       = QStringLiteral("bustpoint_to_bustpoint");        // J01
const QString bustpointToNeckSide_M        = QStringLiteral("bustpoint_to_neck_side");        // J02
const QString bustpointToLowbust_M         = QStringLiteral("bustpoint_to_lowbust");          // J03
const QString bustpointToWaist_M           = QStringLiteral("bustpoint_to_waist");            // J04
const QString bustpointToBustpointHalf_M   = QStringLiteral("bustpoint_to_bustpoint_half");   // J05
const QString bustpointNeckSideToWaist_M   = QStringLiteral("bustpoint_neck_side_to_waist");  // J06
const QString bustpointToShoulderTip_M     = QStringLiteral("bustpoint_to_shoulder_tip");     // J07
const QString bustpointToWaistFront_M      = QStringLiteral("bustpoint_to_waist_front");      // J08
const QString bustpointToBustpointHalter_M = QStringLiteral("bustpoint_to_bustpoint_halter"); // J09
const QString bustpointToShoulderCenter_M  = QStringLiteral("bustpoint_to_shoulder_center");  // J10
// K
const QString shoulderTipToWaistFront_M       = QStringLiteral("shoulder_tip_to_waist_front");        // K01
const QString neckFrontToWaistSide_M          = QStringLiteral("neck_front_to_waist_side");           // K02
const QString neckSideToWaistSideF_M          = QStringLiteral("neck_side_to_waist_side_f");          // K03
const QString shoulderTipToWaistBack_M        = QStringLiteral("shoulder_tip_to_waist_back");         // K04
const QString shoulderTipToWaistB_1inOffset_M = QStringLiteral("shoulder_tip_to_waist_b_1in_offset"); // K05
const QString neckBackToWaistSide_M           = QStringLiteral("neck_back_to_waist_side");            // K06
const QString neckSideToWaistSideB_M          = QStringLiteral("neck_side_to_waist_side_b");          // K07
const QString neckSideToArmfoldF_M            = QStringLiteral("neck_side_to_armfold_f");             // K08
const QString neckSideToArmpitF_M             = QStringLiteral("neck_side_to_armpit_f");              // K09
const QString neckSideToBustSideF_M           = QStringLiteral("neck_side_to_bust_side_f");           // K10
const QString neckSideToArmfoldB_M            = QStringLiteral("neck_side_to_armfold_b");             // K11
const QString neckSideToArmpitB_M             = QStringLiteral("neck_side_to_armpit_b");              // K12
const QString neckSideToBustSideB_M           = QStringLiteral("neck_side_to_bust_side_b");           // K13
// L
const QString armShoulderTipToWristBent_M   = QStringLiteral("arm_shoulder_tip_to_wrist_bent");   // L01
const QString armShoulderTipToElbowBent_M   = QStringLiteral("arm_shoulder_tip_to_elbow_bent");   // L02
const QString armElbowToWristBent_M         = QStringLiteral("arm_elbow_to_wrist_bent");          // L03
const QString armElbowCircBent_M            = QStringLiteral("arm_elbow_circ_bent");              // L04
const QString armShoulderTipToWrist_M       = QStringLiteral("arm_shoulder_tip_to_wrist");        // L05
const QString armShoulderTipToElbow_M       = QStringLiteral("arm_shoulder_tip_to_elbow");        // L06
const QString armElbowToWrist_M             = QStringLiteral("arm_elbow_to_wrist");               // L07
const QString armArmpitToWrist_M            = QStringLiteral("arm_armpit_to_wrist");              // L08
const QString armArmpitToElbow_M            = QStringLiteral("arm_armpit_to_elbow");              // L09
const QString armElbowToWristInside_M       = QStringLiteral("arm_elbow_to_wrist_inside");        // L10
const QString armUpperCirc_M                = QStringLiteral("arm_upper_circ");                   // L11
const QString armAboveElbowCirc_M           = QStringLiteral("arm_above_elbow_circ");             // L12
const QString armElbowCirc_M                = QStringLiteral("arm_elbow_circ");                   // L13
const QString armLowerCirc_M                = QStringLiteral("arm_lower_circ");                   // L14
const QString armWristCirc_M                = QStringLiteral("arm_wrist_circ");                   // L15
const QString armShoulderTipToArmfoldLine_M = QStringLiteral("arm_shoulder_tip_to_armfold_line"); // L16
const QString armNeckSideToWrist_M          = QStringLiteral("arm_neck_side_to_wrist");           // L17
const QString armNeckSideToFingerTip_M      = QStringLiteral("arm_neck_side_to_finger_tip");      // L18
const QString armscyeCirc_M                 = QStringLiteral("armscye_circ");                     // L19
const QString armscyeLength_M               = QStringLiteral("armscye_length");                   // L20
const QString armscyeWidth_M                = QStringLiteral("armscye_width");	                  // L21
const QString armNeckSideToOuterElbow_M     = QStringLiteral("arm_neck_side_to_outer_elbow");     // L22
// M
const QString legCrotchToFloor_M    = QStringLiteral("leg_crotch_to_floor");     // M01
const QString legWaistSideToFloor_M = QStringLiteral("leg_waist_side_to_floor"); // M02
const QString legThighUpperCirc_M   = QStringLiteral("leg_thigh_upper_circ");	 // M03
const QString legThighMidCirc_M     = QStringLiteral("leg_thigh_mid_circ");      // M04
const QString legKneeCirc_M         = QStringLiteral("leg_knee_circ");	         // M05
const QString legKneeSmallCirc_M    = QStringLiteral("leg_knee_small_circ");     // M06
const QString legCalfCirc_M         = QStringLiteral("leg_calf_circ");	         // M07
const QString legAnkleHighCirc_M    = QStringLiteral("leg_ankle_high_circ");     // M08
const QString legAnkleCirc_M        = QStringLiteral("leg_ankle_circ");          // M09
const QString legKneeCircBent_M     = QStringLiteral("leg_knee_circ_bent");	     // M10
const QString legAnkleDiagCirc_M    = QStringLiteral("leg_ankle_diag_circ");     // M11
const QString legCrotchToAnkle_M    = QStringLiteral("leg_crotch_to_ankle");     // M12
const QString legWaistSideToAnkle_M = QStringLiteral("leg_waist_side_to_ankle"); // M13
const QString legWaistSideToKnee_M  = QStringLiteral("leg_waist_side_to_knee");  // M14
// N
const QString crotchLength_M          = QStringLiteral("crotch_length");            // N01
const QString crotchLengthB_M         = QStringLiteral("crotch_length_b");          // N02
const QString crotchLengthF_M         = QStringLiteral("crotch_length_f");          // N03
const QString riseLengthSideSitting_M = QStringLiteral("rise_length_side_sitting"); // N04
const QString riseLengthDiag_M        = QStringLiteral("rise_length_diag");         // N05
const QString riseLengthB_M           = QStringLiteral("rise_length_b");            // N06
const QString riseLengthF_M           = QStringLiteral("rise_length_f");            // N07
const QString riseLengthSide_M        = QStringLiteral("rise_length_side");         // N08
// O
const QString neckBackToWaistFront_M            = QStringLiteral("neck_back_to_waist_front");	           // O01
const QString waistToWaistHalter_M              = QStringLiteral("waist_to_waist_halter");	               // O02
const QString waistNaturalCirc_M                = QStringLiteral("waist_natural_circ");	                   // O03
const QString waistNaturalArcF_M                = QStringLiteral("waist_natural_arc_f");                   // O04
const QString waistNaturalArcB_M                = QStringLiteral("waist_natural_arc_b");                   // O05
const QString waistToNaturalWaistF_M            = QStringLiteral("waist_to_natural_waist_f");              // O06
const QString waistToNaturalWaistB_M            = QStringLiteral("waist_to_natural_waist_b");              // O07
const QString armNeckBackToElbowBent_M          = QStringLiteral("arm_neck_back_to_elbow_bent");           // O08
const QString armNeckBackToWristBent_M          = QStringLiteral("arm_neck_back_to_wrist_bent");           // O09
const QString armNeckSideToElbowBent_M          = QStringLiteral("arm_neck_side_to_elbow_bent");	       // O10
const QString armNeckSideToWristBent_M          = QStringLiteral("arm_neck_side_to_wrist_bent");	       // O11
const QString armAcrossBackCenterToElbowBent_M  = QStringLiteral("arm_across_back_center_to_elbow_bent");  // O12
const QString armAcrossBackCenterToWristBent_M  = QStringLiteral("arm_across_back_center_to_wrist_bent");  // O13
const QString armArmscyeBackCenterToWristBent_M = QStringLiteral("arm_armscye_back_center_to_wrist_bent"); // O14
// P
const QString neckBackToBustFront_M               = QStringLiteral("neck_back_to_bust_front");	                  // P01
const QString neckBackToArmfoldFront_M            = QStringLiteral("neck_back_to_armfold_front");                 // P02
const QString neckBackToArmfoldFrontToWaistSide_M = QStringLiteral("neck_back_to_armfold_front_to_waist_side");   // P03
const QString highbustBackOverShoulderToArmfoldFront_M
                                                = QStringLiteral("highbust_back_over_shoulder_to_armfold_front"); // P04
const QString highbustBackOverShoulderToWaistFront_M
                                                  = QStringLiteral("highbust_back_over_shoulder_to_waist_front"); // P05
const QString neckBackToArmfoldFrontToNeckBack_M  = QStringLiteral("neck_back_to_armfold_front_to_neck_back");    // P06
const QString acrossBackCenterToArmfoldFrontToAcrossBackCenter_M
                                   = QStringLiteral("across_back_center_to_armfold_front_to_across_back_center"); // P07
const QString neckBackToArmfoldFrontToHighbustBack_M
                                                 = QStringLiteral("neck_back_to_armfold_front_to_highbust_back"); // P08
const QString armfoldToArmfoldBust_M              = QStringLiteral("armfold_to_armfold_bust");                    // P09
const QString armfoldToBustFront_M                = QStringLiteral("armfold_to_bust_front");	                  // P10
const QString highbustBOverShoulderToHighbustF_M = QStringLiteral("highbust_b_over_shoulder_to_highbust_f");      // P11
const QString armscyeArc_M                       = QStringLiteral("armscye_arc");	                              // P12
// Q
const QString dartWidthShoulder_M = QStringLiteral("dart_width_shoulder"); // Q01
const QString dartWidthBust_M     = QStringLiteral("dart_width_bust");     // Q02
const QString dartWidthWaist_M    = QStringLiteral("dart_width_waist");    // Q03

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupA()
{
    const QStringList list = QStringList() << height_M                     // A01
                                           << heightNeckBack_M             // A02
                                           << heightScapula_M              // A03
                                           << heightArmpit_M               // A04
                                           << heightWaistSide_M            // A05
                                           << heightHip_M                  // A06
                                           << heightGlutealFold_M          // A07
                                           << heightKnee_M                 // A08
                                           << heightCalf_M                 // A09
                                           << heightAnkleHigh_M            // A10
                                           << heightAnkle_M                // A11
                                           << heightHighhip_M              // A12
                                           << heightWaistFront_M           // A13
                                           << heightBustpoint_M            // A14
                                           << heightShoulderTip_M          // A15
                                           << heightNeckFront_M            // A16
                                           << heightNeckSide_M             // A17
                                           << heightNeckBackToKnee_M       // A18
                                           << heightWaistSideToKnee_M      // A19
                                           << heightWaistSideToHip_M       // A20
                                           << heightKneeToAnkle_M          // A21
                                           << heightNeckBackToWaistSide_M  // A22
                                           << heightWaistBack_M;           // A23
    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupB()
{
    const QStringList list = QStringList() << widthShoulder_M      // B01
                                           << widthBust_M          // B02
                                           << widthWaist_M         // B03
                                           << widthHip_M           // B04
                                           << widthAbdomenToHip_M; // B05

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupC()
{
    const QStringList list = QStringList() << indentNeckBack_M   // C01
                                           << indentWaistBack_M  // C02
                                           << indentAnkleHigh_M; // C03

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupD()
{
    const QStringList list = QStringList() << handPalmLength_M // D01
                                           << handLength_M     // D02
                                           << handPalmWidth_M  // D03
                                           << handPalmCirc_M   // D04
                                           << handCirc_M;      // D05

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupE()
{
    const QStringList list = QStringList() << footWidth_M       // E01
                                           << footLength_M      // E02
                                           << footCirc_M        // E03
                                           << footInstepCirc_M; // E04

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupF()
{
    const QStringList list = QStringList() << headCirc_M	        // F01
                                           << headLength_M          // F02
                                           << headDepth_M	        // F03
                                           << headWidth_M	        // F04
                                           << headCrownToNeckBack_M // F05
                                           << headChinToNeckBack_M; // F06

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupG()
{
    const QStringList list = QStringList() << neckMidCirc_M         // G01
                                           << neckCirc_M            // G02
                                           << highbustCirc_M        // G03
                                           << bustCirc_M            // G04
                                           << lowbustCirc_M         // G05
                                           << ribCirc_M             // G06
                                           << waistCirc_M           // G07
                                           << highhipCirc_M         // G08
                                           << hipCirc_M             // G09
                                           << neckArcF_M            // G10
                                           << highbustArcF_M        // G11
                                           << bustArcF_M            // G12
                                           << size_M                // G12
                                           << lowbustArcF_M         // G13
                                           << ribArcF_M             // G14
                                           << waistArcF_M           // G15
                                           << highhipArcF_M         // G16
                                           << hipArcF_M             // G17
                                           << neckArcHalfF_M        // G18
                                           << highbustArcHalfF_M    // G19
                                           << bustArcHalfF_M        // G20
                                           << lowbustArcHalfF_M     // G21
                                           << ribArcHalfF_M         // G22
                                           << waistArcHalfF_M       // G23
                                           << highhipArcHalfF_M     // G24
                                           << hipArcHalfF_M         // G25
                                           << neckArcB_M            // G26
                                           << highbustArcB_M        // G27
                                           << bustArcB_M            // G28
                                           << lowbustArcB_M         // G29
                                           << ribArcB_M             // G30
                                           << waistArcB_M           // G31
                                           << highhipArcB_M         // G32
                                           << hipArcB_M             // G33
                                           << neckArcHalfB_M        // G34
                                           << highbustArcHalfB_M    // G35
                                           << bustArcHalfB_M        // G36
                                           << lowbustArcHalfB_M     // G37
                                           << ribArcHalfB_M         // G38
                                           << waistArcHalfB_M       // G39
                                           << highhipArcHalfB_M     // G40
                                           << hipArcHalfB_M         // G41
                                           << hipWithAbdomenArcF_M  // G42
                                           << bodyArmfoldCirc_M     // G43
                                           << bodyBustCirc_M        // G44
                                           << bodyTorsoCirc_M       // G45
                                           << hipCircWithAbdomen_M; // G46

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupH()
{
    const QStringList list = QStringList() << neckFrontToWaistF_M              // H01
                                           << neckFrontToWaistFlatF_M          // H02
                                           << armpitToWaistSide_M              // H03
                                           << shoulderTipToWaistSideF_M        // H04
                                           << neckSideToWaistF_M               // H05
                                           << neckSideToWaistBustpointF_M      // H06
                                           << neckFrontToHighbustF_M           // H07
                                           << highbustToWaistF_M               // H08
                                           << neckFrontToBustF_M               // H09
                                           << bustToWaistF_M                   // H10
                                           << lowbustToWaistF_M                // H11
                                           << ribToWaistSide_M                 // H12
                                           << shoulderTipToArmfoldF_M          // H13
                                           << neckSideToBustF_M                // H14
                                           << neckSideToHighbustF_M            // H15
                                           << shoulderCenterToHighbustF_M      // H16
                                           << shoulderTipToWaistSideB_M        // H17
                                           << neckSideToWaistB_M               // H18
                                           << neckBackToWaistB_M               // H19
                                           << neckSideToWaistScapulaB_M        // H20
                                           << neckBackToHighbustB_M            // H21
                                           << highbustToWaistB_M               // H22
                                           << neckBackToBustB_M                // H23
                                           << bustToWaistB_M                   // H24
                                           << lowbustToWaistB_M                // H25
                                           << shoulderTipToArmfoldB_M          // H26
                                           << neckSideToBustB_M                // H27
                                           << neckSideToHighbustB_M            // H28
                                           << shoulderCenterToHighbustB_M      // H29
                                           << waistToHighhipF_M                // H30
                                           << waistToHipF_M                    // H31
                                           << waistToHighhipSide_M             // H32
                                           << waistToHighhipB_M                // H33
                                           << waistToHipB_M                    // H34
                                           << waistToHipSide_M                 // H35
                                           << shoulderSlopeNeckSideAngle_M     // H36
                                           << shoulderSlopeNeckSideLength_M    // H37
                                           << shoulderSlopeNeckBackAngle_M     // H38
                                           << shoulderSlopeNeckBackHeight_M    // H39
                                           << shoulderSlopeShoulderTipAngle_M  // H40
                                           << neckBackToAcrossBack_M           // H41
                                           << acrossBackToWaistB_M;            // H42

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupI()
{
    const QStringList list = QStringList() << shoulderLength_M                // I01
                                           << shoulderTipToShoulderTipF_M     // I02
                                           << acrossChestF_M                  // I03
                                           << armfoldToArmfoldF_M             // I04
                                           << shoulderTipToShoulderTipHalfF_M // I05
                                           << acrossChestHalfF_M              // I06
                                           << shoulderTipToShoulderTipB_M     // I07
                                           << acrossBackB_M                   // I08
                                           << armfoldToArmfoldB_M             // I09
                                           << shoulderTipToShoulderTipHalfB_M // I10
                                           << acrossBackHalfB_M               // I11
                                           << neckFrontToShoulderTipF_M       // I12
                                           << neckBackToShoulderTipB_M        // I13
                                           << neckWidth_M;                    // I14

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupJ()
{
    const QStringList list = QStringList() << bustpointToBustpoint_M        // J01
                                           << bustpointToNeckSide_M         // J02
                                           << bustpointToLowbust_M          // J03
                                           << bustpointToWaist_M            // J04
                                           << bustpointToBustpointHalf_M    // J05
                                           << bustpointNeckSideToWaist_M    // J06
                                           << bustpointToShoulderTip_M      // J07
                                           << bustpointToWaistFront_M       // J08
                                           << bustpointToBustpointHalter_M  // J09
                                           << bustpointToShoulderCenter_M;  // J10

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupK()
{
    const QStringList list = QStringList() << shoulderTipToWaistFront_M       // K01
                                           << neckFrontToWaistSide_M          // K02
                                           << neckSideToWaistSideF_M          // K03
                                           << shoulderTipToWaistBack_M        // K04
                                           << shoulderTipToWaistB_1inOffset_M // K05
                                           << neckBackToWaistSide_M           // K06
                                           << neckSideToWaistSideB_M          // K07
                                           << neckSideToArmfoldF_M            // K08
                                           << neckSideToArmpitF_M             // K09
                                           << neckSideToBustSideF_M           // K10
                                           << neckSideToArmfoldB_M            // K11
                                           << neckSideToArmpitB_M             // K12
                                           << neckSideToBustSideB_M;          // K13

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupL()
{
    const QStringList list = QStringList() << armShoulderTipToWristBent_M   // L01
                                           << armShoulderTipToElbowBent_M   // L02
                                           << armElbowToWristBent_M         // L03
                                           << armElbowCircBent_M            // L04
                                           << armShoulderTipToWrist_M       // L05
                                           << armShoulderTipToElbow_M       // L06
                                           << armElbowToWrist_M             // L07
                                           << armArmpitToWrist_M            // L08
                                           << armArmpitToElbow_M            // L09
                                           << armElbowToWristInside_M       // L10
                                           << armUpperCirc_M                // L11
                                           << armAboveElbowCirc_M           // L12
                                           << armElbowCirc_M                // L13
                                           << armLowerCirc_M                // L14
                                           << armWristCirc_M                // L15
                                           << armShoulderTipToArmfoldLine_M // L16
                                           << armNeckSideToWrist_M          // L17
                                           << armNeckSideToFingerTip_M      // L18
                                           << armscyeCirc_M                 // L19
                                           << armscyeLength_M               // L20
                                           << armscyeWidth_M 	            // L21
                                           << armNeckSideToOuterElbow_M;    // L22

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupM()
{
    const QStringList list = QStringList() << legCrotchToFloor_M    // M01
                                           << legWaistSideToFloor_M // M02
                                           << legThighUpperCirc_M	// M03
                                           << legThighMidCirc_M     // M04
                                           << legKneeCirc_M	        // M05
                                           << legKneeSmallCirc_M    // M06
                                           << legCalfCirc_M	        // M07
                                           << legAnkleHighCirc_M    // M08
                                           << legAnkleCirc_M        // M09
                                           << legKneeCircBent_M	    // M10
                                           << legAnkleDiagCirc_M    // M11
                                           << legCrotchToAnkle_M    // M12
                                           << legWaistSideToAnkle_M // M13
                                           << legWaistSideToKnee_M; // M14

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupN()
{
    const QStringList list = QStringList() << crotchLength_M          // N01
                                           << crotchLengthB_M         // N02
                                           << crotchLengthF_M         // N03
                                           << riseLengthSideSitting_M // N04
                                           << riseLengthDiag_M        // N05
                                           << riseLengthB_M           // N06
                                           << riseLengthF_M           // N07
                                           << riseLengthSide_M;       // N08

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupO()
{
    const QStringList list = QStringList() << neckBackToWaistFront_M 	         // O01
                                           << waistToWaistHalter_M 	             // O02
                                           << waistNaturalCirc_M 	             // O03
                                           << waistNaturalArcF_M                 // O04
                                           << waistNaturalArcB_M                 // O05
                                           << waistToNaturalWaistF_M             // O06
                                           << waistToNaturalWaistB_M             // O07
                                           << armNeckBackToElbowBent_M           // O08
                                           << armNeckBackToWristBent_M           // O09
                                           << armNeckSideToElbowBent_M 	         // O10
                                           << armNeckSideToWristBent_M 	         // O11
                                           << armAcrossBackCenterToElbowBent_M   // O12
                                           << armAcrossBackCenterToWristBent_M   // O13
                                           << armArmscyeBackCenterToWristBent_M; // O14

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupP()
{
    const QStringList list = QStringList() << neckBackToBustFront_M	                             // P01
                                           << neckBackToArmfoldFront_M                           // P02
                                           << neckBackToArmfoldFrontToWaistSide_M                // P03
                                           << highbustBackOverShoulderToArmfoldFront_M           // P04
                                           << highbustBackOverShoulderToWaistFront_M             // P05
                                           << neckBackToArmfoldFrontToNeckBack_M                 // P06
                                           << acrossBackCenterToArmfoldFrontToAcrossBackCenter_M // P07
                                           << neckBackToArmfoldFrontToHighbustBack_M             // P08
                                           << armfoldToArmfoldBust_M                             // P09
                                           << armfoldToBustFront_M	                             // P10
                                           << highbustBOverShoulderToHighbustF_M                 // P11
                                           << armscyeArc_M;	                                     // P12

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListGroupQ()
{
    const QStringList list = QStringList() << dartWidthShoulder_M // Q01
                                           << dartWidthBust_M 	  // Q02
                                           << dartWidthWaist_M;   // Q03

    return list;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList ListNumbers(const VTranslateMeasurements *trM, const QStringList &listMeasurements)
{
    SCASSERT(trM != nullptr)

    QStringList numbers;
    for (auto &m : listMeasurements)
    {
        numbers.append(trM->MNumber(m));
    }
    return numbers;
}

//---------------------------------------------------------------------------------------------------------------------
QString MapDiagrams(const VTranslateMeasurements *trM, const QString &number)
{
    switch (ListNumbers(trM, ListGroupA()).indexOf(number))
    {
        // A
        case 0: // A01
        case 1: // A02
        case 2: // A03
        case 3: // A04
        case 4: // A05
        case 5: // A06
        case 6: // A07
        case 7: // A08
        case 8: // A09
        case 9: // A10
        case 10: // A11
        case 11: // A12
        case 12: // A13
        case 13: // A14
        case 14: // A15
        case 15: // A16
        case 16: // A17
            return QStringLiteral("Ap1");
        case 17: // A18
        case 18: // A19
        case 19: // A20
        case 20: // A21
        case 21: // A22
        case 22: // A23
            return QStringLiteral("Ap2");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupB()).indexOf(number))
    {
        // B
        case 0: // B01
        case 1: // B02
        case 2: // B03
        case 3: // B04
            return QStringLiteral("Bp1");
        case 4: // B05
            return QStringLiteral("Bp2");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupC()).indexOf(number))
    {
        // C
        case 0: // C01
            return QStringLiteral("Cp1");
        case 1: // C02
        case 2: // C03
            return QStringLiteral("Cp2");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupD()).indexOf(number))
    {
        // D
        case 0: // D01
        case 1: // D02
        case 2: // D03
            return QStringLiteral("Dp1");
        case 3: // D04
            return QStringLiteral("Dp2");
        case 4: // D05
            return QStringLiteral("Dp3");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupE()).indexOf(number))
    {
        // E
        case 0: // E01
            return QStringLiteral("Ep1");
        case 1: // E02
        case 2: // E03
        case 3: // E04
            return QStringLiteral("Ep2");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupF()).indexOf(number))
    {
        // F
        case 0: // F01
        case 1: // F02
        case 2: // F03
            return QStringLiteral("Fp1");
        case 3: // F04
            return QStringLiteral("Fp2");
        case 4: // F05
        case 5: // F06
            return QStringLiteral("Fp3");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupG()).indexOf(number))
    {
        // G
        case 0: // G01
        case 1: // G02
        case 2: // G03
        case 3: // G04
        case 4: // G05
        case 5: // G06
        case 6: // G07
        case 7: // G08
        case 8: // G09
            return QStringLiteral("Gp1");
        case 9: // G10
        case 10: // G11
        case 11: // G12
        case 12: // G12
        case 13: // G13
        case 14: // G14
        case 15: // G15
        case 16: // G16
        case 17: // G17
            return QStringLiteral("Gp2");
        case 18: // G18
        case 19: // G19
        case 20: // G20
        case 21: // G21
        case 22: // G22
        case 23: // G23
        case 24: // G24
        case 25: // G25
            return QStringLiteral("Gp3");
        case 26: // G26
        case 27: // G27
        case 28: // G28
        case 29: // G29
        case 30: // G30
        case 31: // G31
        case 32: // G32
        case 33: // G33
            return QStringLiteral("Gp4");
        case 34: // G34
        case 35: // G35
        case 36: // G36
        case 37: // G37
        case 38: // G38
        case 39: // G39
        case 40: // G40
        case 41: // G41
            return QStringLiteral("Gp5");
        case 42: // G42
            return QStringLiteral("Gp6");
        case 43: // G43
        case 44: // G44
            return QStringLiteral("Gp7");
        case 45: // G45
            return QStringLiteral("Gp8");
        case 46: // G46
            return QStringLiteral("Gp9");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupH()).indexOf(number))
    {
        // H
        case 0: // H01
            return QStringLiteral("Hp1");
        case 1: // H02
            return QStringLiteral("Hp2");
        case 2: // H03
        case 3: // H04
        case 4: // H05
        case 5: // H06
            return QStringLiteral("Hp3");
        case 6: // H07
        case 7: // H08
        case 8: // H09
        case 9: // H10
        case 10: // H11
        case 11: // H12
            return QStringLiteral("Hp4");
        case 12: // H13
        case 13: // H14
        case 14: // H15
        case 15: // H16
            return QStringLiteral("Hp5");
        case 16: // H17
        case 17: // H18
        case 18: // H19
        case 19: // H20
            return QStringLiteral("Hp6");
        case 20: // H21
        case 21: // H22
        case 22: // H23
        case 23: // H24
        case 24: // H25
            return QStringLiteral("Hp7");
        case 25: // H26
        case 26: // H27
        case 27: // H28
        case 28: // H29
            return QStringLiteral("Hp8");
        case 29: // H30
        case 30: // H31
        case 31: // H32
            return QStringLiteral("Hp9");
        case 32: // H33
        case 33: // H34
        case 34: // H35
            return QStringLiteral("Hp10");
        case 35: // H36
        case 36: // H37
        case 37: // H38
        case 38: // H39
            return QStringLiteral("Hp11");
        case 39: // H40
            return QStringLiteral("Hp12");
        case 40: // H41
        case 41: // H42
            return QStringLiteral("Hp13");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupI()).indexOf(number))
    {
        // I
        case 0: // I01
        case 1: // I02
        case 2: // I03
        case 3: // I04
            return QStringLiteral("Ip1");
        case 4: // I05
        case 5: // I06
            return QStringLiteral("Ip2");
        case 6: // I07
        case 7: // I08
        case 8: // I09
            return QStringLiteral("Ip3");
        case 9: // I10
        case 10: // I11
            return QStringLiteral("Ip4");
        case 11: // I12
            return QStringLiteral("Ip5");
        case 12: // I13
            return QStringLiteral("Ip6");
        case 13: // I14
            return QStringLiteral("Ip7");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupJ()).indexOf(number))
    {
        // J
        case 0: // J01
        case 1: // J02
        case 2: // J03
        case 3: // J04
            return QStringLiteral("Jp1");
        case 4: // J05
            return QStringLiteral("Jp2");
        case 5: // J06
            return QStringLiteral("Jp3");
        case 6: // J07
        case 7: // J08
            return QStringLiteral("Jp4");
        case 8: // J09
            return QStringLiteral("Jp5");
        case 9: // J10
            return QStringLiteral("Jp6");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupK()).indexOf(number))
    {
        // K
        case 0: // K01
            return QStringLiteral("Kp1");
        case 1: // K02
        case 2: // K03
            return QStringLiteral("Kp2");
        case 3: // K04
            return QStringLiteral("Kp3");
        case 4: // K05
            return QStringLiteral("Kp4");
        case 5: // K06
        case 6: // K07
            return QStringLiteral("Kp5");
        case 7: // K08
            return QStringLiteral("Kp6");
        case 8: // K09
            return QStringLiteral("Kp7");
        case 9: // K10
            return QStringLiteral("Kp8");
        case 10: // K11
            return QStringLiteral("Kp9");
        case 11: // K12
            return QStringLiteral("Kp10");
        case 12: // K13
            return QStringLiteral("Kp11");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupL()).indexOf(number))
    {
        // L
        case 0: // L01
        case 1: // L02
        case 2: // L03
        case 3: // L04
            return QStringLiteral("Lp1");
        case 4: // L05
        case 5: // L06
        case 6: // L07
            return QStringLiteral("Lp2");
        case 7: // L08
        case 8: // L09
        case 9: // L10
            return QStringLiteral("Lp3");
        case 10: // L11
        case 11: // L12
        case 12: // L13
        case 13: // L14
        case 14: // L15
            return QStringLiteral("Lp4");
        case 15: // L16
            return QStringLiteral("Lp5");
        case 16: // L17
            return QStringLiteral("Lp6");
        case 17: // L18
            return QStringLiteral("Lp7");
        case 18: // L19
        case 19: // L20
            return QStringLiteral("Lp8");
        case 20: // L21
            return QStringLiteral("Lp9");
        case 21: // L22
            return QStringLiteral("Lp10");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupM()).indexOf(number))
    {
        // M
        case 0: // M01
        case 1: // M02
            return QStringLiteral("Mp1");
        case 2: // M03
        case 3: // M04
        case 4: // M05
        case 5: // M06
        case 6: // M07
        case 7: // M08
        case 8: // M09
        case 9: // M10
        case 10: // M11
            return QStringLiteral("Mp2");
        case 11: // M12
        case 12: // M13
        case 13: // M14
            return QStringLiteral("Mp3");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupN()).indexOf(number))
    {
        // N
        case 0: // N01
            return QStringLiteral("Np1");
        case 1: // N02
        case 2: // N03
            return QStringLiteral("Np2");
        case 3: // N04
        case 4: // N05
            return QStringLiteral("Np3");
        case 5: // N06
        case 6: // N07
            return QStringLiteral("Np4");
        case 7: // N08
            return QStringLiteral("Np5");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupO()).indexOf(number))
    {
        // O
        case 0: // O01
            return QStringLiteral("Op1");
        case 1: // O02
            return QStringLiteral("Op2");
        case 2: // O03
            return QStringLiteral("Op3");
        case 3: // O04
            return QStringLiteral("Op4");
        case 4: // O05
            return QStringLiteral("Op5");
        case 5: // O06
            return QStringLiteral("Op6");
        case 6: // O07
            return QStringLiteral("Op7");
        case 7: // O08
        case 8: // O09
            return QStringLiteral("Op8");
        case 9: // O10
        case 10: // O11
            return QStringLiteral("Op9");
        case 11: // O12
        case 12: // O13
            return QStringLiteral("Op10");
        case 13: // O14
            return QStringLiteral("Op11");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupP()).indexOf(number))
    {
        // P
        case 0: // P01
            return QStringLiteral("Pp1");
        case 1: // P02
            return QStringLiteral("Pp2");
        case 2: // P03
            return QStringLiteral("Pp3");
        case 3: // P04
            return QStringLiteral("Pp4");
        case 4: // P05
            return QStringLiteral("Pp5");
        case 5: // P06
            return QStringLiteral("Pp6");
        case 6: // P07
            return QStringLiteral("Pp7");
        case 7: // P08
            return QStringLiteral("Pp8");
        case 8: // P09
            return QStringLiteral("Pp9");
        case 9: // P10
            return QStringLiteral("Pp10");
        case 10: // P11
            return QStringLiteral("Pp11");
        case 11: // P12
            return QStringLiteral("Pp12");
        default:
            break;
    }

    switch (ListNumbers(trM, ListGroupQ()).indexOf(number))
    {
        // Q
        case 0: // Q01
            return QStringLiteral("Qp1");
        case 1: // Q02
            return QStringLiteral("Qp2");
        case 2: // Q03
            return QStringLiteral("Qp3");
        default:
            break;
    }

    return QString();
}

//---------------------------------------------------------------------------------------------------------------------
QStringList AllGroupNames()
{
    const QStringList originalNames = QStringList() << ListGroupA()
                                                    << ListGroupB()
                                                    << ListGroupC()
                                                    << ListGroupD()
                                                    << ListGroupE()
                                                    << ListGroupF()
                                                    << ListGroupG()
                                                    << ListGroupH()
                                                    << ListGroupI()
                                                    << ListGroupJ()
                                                    << ListGroupK()
                                                    << ListGroupL()
                                                    << ListGroupM()
                                                    << ListGroupN()
                                                    << ListGroupO()
                                                    << ListGroupP()
                                                    << ListGroupQ();

    return originalNames;
}
