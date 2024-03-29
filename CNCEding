#pragma once
#include "CNCBase.h"
#include "cncapi.h"
using namespace std;

class Eding : public CNCBase {
  public: int Login() {
          CNC_RC loginRC = CncConnectServer((char*)"cnc.ini");
          return loginRC;
  };
  public: int Logout() {
          CNC_RC logoutRC = CncDisConnectServer();
          return logoutRC;
  };
  public: string Get_VendorName() {
          string VendorName = "EdingCNC";
          return VendorName;
  };
  public: string Get_VendorRevision() {
          char* ServerVersion = new char();
          CncGetServerVersion((char*)ServerVersion);
          return ServerVersion;
  };
  public: string Get_CSVersion() {
          return "1.0";
  };
  public: double Get_tcp_bcs_a_actpos() {
          double d_MachineCoordtsA = CncGetMachinePosition().a;
          return d_MachineCoordtsA;
  };
  public: double Get_tcp_bcs_b_actpos() {
          double d_MachineCoordtsB = CncGetMachinePosition().b;
          return d_MachineCoordtsB;
  };
  public: double Get_tcp_bcs_c_actpos() {
          double d_MachineCoordtsC = CncGetMachinePosition().c;
          return d_MachineCoordtsC;
  };
  public: double Get_tcp_bcs_x_actpos() {
          double d_MachineCoordtsX = CncGetMachinePosition().x;
          return d_MachineCoordtsX;
  };
  public: double Get_tcp_bcs_y_actpos() {
          double d_MachineCoordtsY = CncGetMachinePosition().y;
          return d_MachineCoordtsY;
  };
  public: double Get_tcp_bcs_z_actpos() {
          double d_MachineCoordtsZ = CncGetMachinePosition().z;
          return d_MachineCoordtsZ;
  };
  public: double Get_tcp_wcs_a_actpos() {
          double d_WorkCoordtsA = CncGetWorkPosition().a;
//        axis id (X=0, Y=1, .. C=5)
          return d_WorkCoordtsA;
  }; 
  public: double Get_tcp_wcs_b_actpos() {
          double d_WorkCoordtsB = CncGetWorkPosition().b;
          return d_WorkCoordtsB;
  };
  public: double Get_tcp_wcs_c_actpos() {
          double d_WorkCoordtsC = CncGetWorkPosition().c;
          return d_WorkCoordtsC;
  };
  public: double Get_tcp_wcs_x_actpos() {
          double d_WorkCoordtsX = CncGetWorkPosition().x;
          return d_WorkCoordtsX;
  };
  public: double Get_tcp_wcs_y_actpos() {
          double d_WorkCoordtsY = CncGetWorkPosition().y;
          return d_WorkCoordtsY;
  };
  public: double Get_tcp_wcs_z_actpos() {
          double d_WorkCoordtsZ = CncGetWorkPosition().z;
          return d_WorkCoordtsZ;
  };
  public: double Get_s1_act_speed() {
          return CncGetProgrammedSpeed();
  };
  public: string Get_ActGFunctions() {
          char* activeGCodes = new char[80];
          CncGetCurrentGcodesText(activeGCodes);
          string sGCodes = activeGCodes;
          return sGCodes;
  };
  public: string Get_ActMFunctions() {
          char* activeMCodes = new char[80];
          CncGetCurrentMcodesText(activeMCodes);
          string sMCodes = activeMCodes;
          return sMCodes;
  };
  public: string CurrentILineText() {
          char* cCILineText = new char[1055];
          CncGetCurInterpreterLineText(cCILineText);
          string sCILineText = cCILineText;
          return sCILineText;
  };
  public: string InterpreterNextLineText() {
      char* cInterpreterNextLine = new char[80];
      int*   iCILTNextLine = new int;
      CncFindNextJobLine(cInterpreterNextLine, iCILTNextLine);
      string sCILTNextLine = cInterpreterNextLine;
      return sCILTNextLine;
  };
  public: int Get_tool_offset() {
  };
  public: string Get_act_main_program_file() {
          wchar_t* pJobName = new wchar_t[95];
          CNC_JOB_STATUS* pJobStatus = CncGetJobStatus();
          pJobName = pJobStatus->jobName;
          int array_sizePN = 95;
          string n = "";
          int i;
          for (auto i = 0; i < array_sizePN; i++)
          {
              std::wstring;
              n += pJobName[i];
          }
          return n;
  };
  public: char* Get_active_program_block() {
      char* pJobLT = new char[1056];
      CNC_JOB_STATUS* pJobStatus2 = CncGetJobStatus();
      pJobLT = pJobStatus2->curIpLineText;
      return pJobLT;
  };
  public: string Get_alarms_message() {
          CNC_RC logAM_RC;
          CNC_LOG_MESSAGE* logM = new CNC_LOG_MESSAGE();
          logAM_RC = CncLogFifoGet((CNC_LOG_MESSAGE*)logM);
          string slogM = string(logM->text);
          return slogM;
  };
  public: string Get_error_detail(int rc) {
          return CncGetRCText((CNC_RC)rc);
  };
  public: int LoadJob(const wchar_t* fileName) {
          return CncLoadJobW(fileName);
  };
  public: int PauseJob() {
          return CncPauseJob();
  };
  public: int RunOrResumeJob() {
          return CncRunOrResumeJob();
  };
  public: int RewindJob() {
          CNC_RC RewindJobRC = CncRewindJob();
          return RewindJobRC;
  };
  public: int RenderGraph(int outLines, int contour) {
          return CncStartRenderGraph(outLines, contour);
  };
  public: int Reset() {
          return CncReset();
  };
  public: bool CheckJointHomed(int jointN) {
          int JointHomed = CncGetJointStatus(jointN)->isHomed;
          if (JointHomed == 0) {
              return false;
          }
          else {
              if (JointHomed == 1) {
                  return true;
              };
          };
  };
  public: bool CheckSimulationMode() {
          int boolSimulationMode = CncGetSimulationMode();
          if (boolSimulationMode == 1) {
// Modo Simulação Ativo -> CncAxis IsVirtual true.
// Não foi detetado hardware conectado ao EdingCNC.
              return true;
          }
          else {
              if (boolSimulationMode == 0) {
// Modo Simulação Desativo -> CncAxis IsVirtual false.
// Detetado hardware conectado ao EdingCNC -> Modo Operacional Normal.
                  return false;
              };
          };
  };
  public: double Get_MachineOriginXOffset() {
          return CncGetActualOriginOffset().x;
  };
  public: double Get_MachineOriginYOffset() {
          return CncGetActualOriginOffset().y;
  };
  public: double Get_MachineOriginZOffset() {
          return CncGetActualOriginOffset().z;
  };
  public: int Get_ToolIDinSpindle() {
          return CncGetCurrentToolNumber();
  };
  public: bool Get_SingleStepMode() {
          int iCheckSingleMode = CncGetSingleStepMode();
          if (iCheckSingleMode == 1) {
              return true;
          }
          else {
              if (iCheckSingleMode == 0) {
                  return false;
              };
          };
  };
  public: double Get_S1_CmdFeedOverride() {
          double dS1FeedOverride = CncGetActualFeedOverride();
          return dS1FeedOverride;
  };
  public: double Get_S1_CmdSpeedOverride() {
          double dS1SpeedOverride = CncGetActualSpeedOverride();
          return dS1SpeedOverride;
  };
  public: double Get_S1_ProgrammedSpeed() {
          double dS1ProgSp = CncGetProgrammedSpeed();
          double dS1ProgrammedSpeed = dS1ProgSp / 60;
          return dS1ProgrammedSpeed;
  };
  public: double Get_S1_ProgrammedFeed() {
          double dS1ProgrammedFeed = CncGetProgrammedFeed();
          return dS1ProgrammedFeed;
  };
  public: int Get_S1_TurnDirection() {
         int iS1TurnDirection = CncGetSpindleStatus()->spindleDirection;
          if (iS1TurnDirection == 0) {
//        In EdingCNC.API : 0 -> Clockwise (C) | In OPCUA CS : 1 -> C
              return 1;
          }
          else {
              if (iS1TurnDirection == 1) {
// In EdingCNC.API : 1 -> CounterClockwise (CC) | In OPCUA CS : 2 -> CC
                  return 2;
              };
          };
  };
  public: bool Get_SimulationMode() {
          int iCncSimulationMode = CncGetSimulationMode();
//        0 -> Real Operation | 1 -> Simulation | 2 -> Fast Simulation
          if (iCncSimulationMode == 0) {
              return false;
          }
          else {
             if (iCncSimulationMode == 1) {
                return true;
             }
             else {
                if (iCncSimulationMode == 2) {
                    return true;
                };
             };
          };
  };
  public: int Get_ChannelActStatus() {
          int iChannelStatus = CncGetState();
          int iErrorSwLimit = CncGetSwLimitError();
          int iErrorFifo = CncGetFifoError();
          int iErrorEStop = CncGetEMStopActive();

          if (iErrorSwLimit == 1 || iErrorFifo == 1 || iErrorEStop == 1) {
              return 1;
          }
          else {
               switch (iChannelStatus) {
//        Channel Status -- Reset -> 2 | Active -> 0 | Error -> 1
               case 0:
                   return 2;
                   break;
               case 1:
                   return 2;
                   break;
               case 2:
                   return 0;
                   break;
               case 6:
                   return 0;
                   break;
               case 7:
                   return 0;
                   break;
               case 8:
                   return 0;
                   break;
               case 9:
                   return 0;
                   break;
               case 10:
                   return 0;
                   break;
               case 11:
                   return 0;
                   break;
               case 12:
                   return 0;
                   break;
               case 13:
                   return 0;
                   break;
               case 14:
                   return 0;
                   break;
               case 15:
                   return 0;
                   break;
               case 16:
                   return 0;
                   break;
               case 17:
                   return 0;
                   break;
               case 18:
                   return 0;
                   break;
               case 19:
                   return 0;
                   break;
               case 20:
                   return 0;
                   break;
               case 21:
                   return 0;
                   break;
               case 22:
                   return 0;
                   break;
               case 23:
                   return 0;
                   break;
               case 3:
                   return 1;
                   break;
               case 4:
                   return 1;
                   break;
               case 5:
                   return 1;
                   break;
               };
          };
  };
};
