Full Data Type Name                                  | DDTID |   Type Signature   |  Max Bit Len
--------------------------------------------------------------------------------------------------
uavcan.CoarseOrientation                                 N/A   0x271ba10b0dac9e52      16
uavcan.Timestamp                                         N/A   0x05bd0b5c81087e0d      56
uavcan.equipment.actuator.ArrayCommand                  1010   0xd8a7486238ec3af3     484
uavcan.equipment.actuator.Command                        N/A   0x8d9a6a920c1d616c      32
uavcan.equipment.actuator.Status                        1011   0x5e9bba44faf1ea04      64
uavcan.equipment.ahrs.MagneticFieldStrength             1001   0xe2a7d4a9460bc2f2     196
uavcan.equipment.ahrs.MagneticFieldStrength2            1002   0xb6ac0c442430297e     204
uavcan.equipment.ahrs.RawIMU                            1003   0x8280632c40e574b5     958
uavcan.equipment.ahrs.Solution                          1000   0x72a63a3c6f41fa9b     668
uavcan.equipment.air_data.AngleOfAttack                 1025   0xd5513c3f7afac74e      40
uavcan.equipment.air_data.IndicatedAirspeed             1021   0x0a1892d72ab8945f      32
uavcan.equipment.air_data.RawAirData                    1027   0xc77df38ba122f5da     397
uavcan.equipment.air_data.Sideslip                      1026   0x7b48e55fcff42a57      32
uavcan.equipment.air_data.StaticPressure                1028   0xcdc7c43412bdc89a      48
uavcan.equipment.air_data.StaticTemperature             1029   0x49272a6477d96271      32
uavcan.equipment.air_data.TrueAirspeed                  1020   0x306f69e0a591afaa      32
uavcan.equipment.camera_gimbal.AngularCommand           1040   0x4af6e57b2b2be29c      80
uavcan.equipment.camera_gimbal.GEOPOICommand            1041   0x9371428a92f01fd6     104
uavcan.equipment.camera_gimbal.Mode                      N/A   0x9108c7785aeb69c4       8
uavcan.equipment.camera_gimbal.Status                   1044   0xb9f127865be0d61e     228
uavcan.equipment.device.Temperature                     1110   0x70261c28a94144c6      40
uavcan.equipment.esc.RPMCommand                         1031   0xce0f9f621cf7e70b     365
uavcan.equipment.esc.RawCommand                         1030   0x217f5c87d7ec951d     285
uavcan.equipment.esc.Status                             1034   0xa9af28aea2fbb254     110
uavcan.equipment.gnss.Auxiliary                         1061   0x9be8bdc4c3dbbfd2     125
uavcan.equipment.gnss.ECEFPositionVelocity               N/A   0x24a5da4abee3a248     792
uavcan.equipment.gnss.Fix                               1060   0x54c1572b9e07f297     628
uavcan.equipment.gnss.Fix2                              1063   0xca41e7000f37435f    1769
uavcan.equipment.gnss.RTCMStream                        1062   0x1f56030ecb171501    1040
uavcan.equipment.hardpoint.Command                      1070   0xa1a036268b0c3455      24
uavcan.equipment.hardpoint.Status                       1071   0x624a519d42553d82      56
uavcan.equipment.ice.FuelTankStatus                     1129   0x286b4a387ba84bc4     104
uavcan.equipment.ice.reciprocating.CylinderStatus        N/A   0xd68ac83a89d5b36b      80
uavcan.equipment.ice.reciprocating.Status               1120   0xd38aa3ee75537ec6    1565
uavcan.equipment.indication.BeepCommand                 1080   0xbe9ea9fec2b15d52      32
uavcan.equipment.indication.LightsCommand               1081   0x2031d93c8bdd1ec4     485
uavcan.equipment.indication.RGB565                       N/A   0x58a7cef41951ec34      16
uavcan.equipment.indication.SingleLightCommand           N/A   0xe894b8b589807007      24
uavcan.equipment.power.BatteryInfo                      1092   0x249c26548a711966     437
uavcan.equipment.power.CircuitStatus                    1091   0x8313d33d0ddda115      56
uavcan.equipment.power.PrimaryPowerSupplyStatus         1090   0xbba05074ad757480      47
uavcan.equipment.range_sensor.Measurement               1050   0x68fffe70fc771952     120
uavcan.equipment.safety.ArmingStatus                    1100   0x8700f375556a8003       8
uavcan.navigation.GlobalNavigationSolution              2000   0x463b10cccbe51c3d    1860
uavcan.protocol.AccessCommandShell                         6   0x59276b5921c9246e    1040 / 2097
uavcan.protocol.CANIfaceStats                            N/A   0x13b106f0c44ca350     144
uavcan.protocol.DataTypeKind                             N/A   0x9420a73e008e5930       8
uavcan.protocol.GetDataTypeInfo                            2   0x1b283338a7bed2d8     671 / 743
uavcan.protocol.GetNodeInfo                                1   0xee468a8121c46a9e       0 / 3015
uavcan.protocol.GetTransportStats                          4   0xbe6f76a7ec312b04       0 / 578
uavcan.protocol.GlobalTimeSync                             4   0x20271116a793c2db      56
uavcan.protocol.HardwareVersion                          N/A   0x0ad5c4c933f4a0c4    2192
uavcan.protocol.NodeStatus                               341   0x0f0868d0c1a7c6f1      56
uavcan.protocol.Panic                                      5   0x8b79b4101811c1d7      59
uavcan.protocol.RestartNode                                5   0x569e05394a3017f0      40 / 1
uavcan.protocol.SoftwareVersion                          N/A   0xdd46fd376527fea1     120
uavcan.protocol.debug.KeyValue                         16370   0xe02f25d6e0c98ae0     502
uavcan.protocol.debug.LogLevel                           N/A   0x711bf141af572346       3
uavcan.protocol.debug.LogMessage                       16383   0xd654a48e0c049d75     983
uavcan.protocol.dynamic_node_id.Allocation                 1   0x0b2a812620a11d40     141
uavcan.protocol.dynamic_node_id.server.AppendEntries      30   0x8032c7097b48a3cc     249 / 33
uavcan.protocol.dynamic_node_id.server.Discovery         390   0x821ae2f525f69f21      51
uavcan.protocol.dynamic_node_id.server.Entry             N/A   0x7faa779d64fa75c2     168
uavcan.protocol.dynamic_node_id.server.RequestVote        31   0xcdde07bb89a56356      72 / 33
uavcan.protocol.enumeration.Begin                         15   0x196ae06426a3b5d8     759 / 8
uavcan.protocol.enumeration.Indication                   380   0x884cb63050a84f35     815
uavcan.protocol.file.BeginFirmwareUpdate                  40   0xb7d725df72724126    1616 / 1031
uavcan.protocol.file.Delete                               47   0x78648c99170b47aa    1608 / 16
uavcan.protocol.file.EntryType                           N/A   0x6924572fbb2086e5       8
uavcan.protocol.file.Error                               N/A   0xa83071ffea4fae15      16
uavcan.protocol.file.GetDirectoryEntryInfo                46   0x8c46e8ab568bda79    1640 / 1632
uavcan.protocol.file.GetInfo                              45   0x5004891ee8a27531    1608 / 64
uavcan.protocol.file.Path                                N/A   0x12aefc50878a43e2    1608
uavcan.protocol.file.Read                                 48   0x8dcdca939f33f678    1648 / 2073
uavcan.protocol.file.Write                                49   0x515aa1dc77e58429    3192 / 16
uavcan.protocol.param.Empty                              N/A   0x6c4d0e8ef37361df       0
uavcan.protocol.param.ExecuteOpcode                       10   0x3b131ac5eb69d2cd      56 / 49
uavcan.protocol.param.GetSet                              11   0xa7b622f939d1a4d5    1791 / 2967
uavcan.protocol.param.NumericValue                       N/A   0x0da6d6fea22e3587      66
uavcan.protocol.param.Value                              N/A   0x29f14bf484727267    1035