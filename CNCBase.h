#pragma once
#ifndef CNCBASE_H
#define CNCBASE_H

using namespace std;

class CNC_Base {

    public: int Login();

    public: int Logout();

    public: string Get_VendorName();

    public: string Get_VendorRevision();

    public: string Get_CompanionSpecificationVersion();

    public: string Get_act_main_program_file();

    public: string Get_alarms_message();

    public: int Get_emergency();

    public: int LoadJob(const wchar_t* fileName);

    public: int PauseJob();

    public: int RunOrResumeJob();

    public: int RewindJob();

    public: int RenderGraph(int outLines, int contour);

    public: int CncWatchDog();

    public: int Reset();

    public: int CurrentILineText();

    public: string Get_error_detail();

    public: double Get_tcp_bcs_a_actpos();

    public: double Get_tcp_bcs_b_actpos();

    public: double Get_tcp_bcs_c_actpos();

    public: double Get_tcp_bcs_x_actpos();

    public: double Get_tcp_bcs_y_actpos();

    public: double Get_tcp_bcs_z_actpos();

    public: double Get_tcp_wcs_a_actpos();

    public: double Get_tcp_wcs_b_actpos();

    public: double Get_tcp_wcs_c_actpos();

    public: double Get_tcp_wcs_x_actpos();

    public: double Get_tcp_wcs_y_actpos();

    public: double Get_tcp_wcs_z_actpos();

    public: double Get_s1_act_speed();

    public: string Get_ActGFunctions();

    public: string Get_ActMFunctions();

    public: char Get_active_program_block();

    public: int Get_active_program_block_line();

    public: int Get_tool_offset();

    public: bool Get_x_is_inactive();

    public: bool Get_x_is_virtual();
   
    public: bool Get_x_is_referenced();

    public: bool Get_x_is_rotational();

    public: float Get_x_dir_pos();

    public: float Get_x_dir_actpos();

    public: float Get_x_dir_cmdpos();

    public: float Get_x_dir_remdist();

    public: float Get_x_indir_pos();

    public: double Get_x_indir_actpos();

    public: float Get_x_indir_cmdpos();

    public: float Get_x_indir_remdist();

    public: double Get_x_zero_offset();

    public: double Get_y_zero_offset();

    public: double Get_z_zero_offset();

    public: int Get_x_act_channel();

    public: bool CheckJointHomed(int jointN);

    public: bool CheckSimulationMode();

    public: double Get_MachineOriginXOffset();

    public: double Get_MachineOriginYOffset();

    public: int Get_ToolIDinSpindle();

    public: bool Get_SingleStepMode();

    public: double Get_S1_CmdFeedOverride();

    public: double Get_S1_CmdSpeedOverride();

    public: double Get_S1_ProgrammedFeed();

    public: double Get_S1_ProgrammedSpeed();

    public: int Get_S1_TurnDirection();

    public: int Get_SimulationMode();

    public: int Get_ChannelActStatus();
   
};

#endif
