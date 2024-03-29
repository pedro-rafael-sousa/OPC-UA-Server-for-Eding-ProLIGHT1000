#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h> 
#include <open62541/server_config_default.h>
#include "cnc_nodeids.h"
#include "namespace_cnc_generated.h"
#include "namespace_cnctest_generated.h"
#include "signal.h"
#include <sstream>
#include "stdlib.h"
#include <string>
#include <vector>
#include "cncapi.h"
#include "CNCEding.h"
#include "pugixml.hpp"

using namespace std;
using namespace pugi;

UA_Boolean running = true;

class ElementFunction_GenericCncClass {
    public: string xmlKey; string xmlValue;
};

class ValueElementFunction_GenericCncClass {
    public: string xmlValue_Name; bool xmlValue_Bool; int xmlValue_Period;
};

class VectFunctions_GenericCncClass {
    public: vector<ElementFunction_GenericCncClass> vectFunctions_GCC;
};


static VectFunctions_GenericCncClass XmlParse () {

    ElementFunction_GenericCncClass elemFunction_GCC;
    static vector<ElementFunction_GenericCncClass> vectElemFunction_GCC;

    pugi::xml_document xml_doc;
    pugi::xml_parse_result xmlRead_Result = xml_doc.load_file("cnc.xml");
    pugi::xml_node xmlResult_lines = xml_doc.child("parameters");

    for (pugi::xml_node lineAdd : xmlResult_lines) {
      elemFunction_GCC.xmlKey = string(lineAdd.attribute("key").value());
      elemFunction_GCC.xmlValue = string(lineAdd.attribute("value").value());
      vectElemFunction_GCC.push_back(elemFunction_GCC);
    };
    
    VectFunctions_GenericCncClass instanciaVectFunct_GCC_lido;

    for (auto elemFunction : vectElemFunction_GCC) {
      instanciaVectFunct_GCC_lido.vectFunctions_GCC.push_back(elemFunction);
    };

    string modelo = vectElemFunction_GCC[0].xmlValue;
    string ip = vectElemFunction_GCC[1].xmlValue;
    string port = vectElemFunction_GCC[2].xmlValue;

    return instanciaVectFunct_GCC_lido;
};


static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c"); running = false;
};


CNC_Eding  ProLight1000;

//  Informações que são Atualizadas Apenas 1 Vez
static void StaticValues(UA_Server* server) {

    //   VendorName
    string sEding_VendorName = ProLight1000.Get_VendorName();
    UA_String uaString_VendorName = UA_STRING((char*)sEding_VendorName.c_str());
    UA_NodeId uaNode_VendorName = UA_NODEID_STRING(3, "a.s6001");
    UA_Variant uaVariant_VendorName;
    UA_Variant_init(&uaVariant_VendorName);
    UA_Variant_setScalar(&uaVariant_VendorName, &uaString_VendorName, &UA_TYPES[UA_TYPES_STRING]);
    UA_Server_writeValue(server, uaNode_VendorName, uaVariant_VendorName);
    UA_Server_writeAccessLevel(server, uaNode_VendorName, UA_ACCESSLEVELMASK_READ);

    //   VendorRevision
    string sEding_VendorRevision = ProLight1000.Get_VendorRevision();
    UA_String uaString_VendorRevision = UA_STRING((char*)sEding_VendorRevision.c_str());
    UA_NodeId uaNode_VendorRevision = UA_NODEID_STRING(3, "a.s6002");
    UA_Variant uaVariant_VendorRevision;
    UA_Variant_init(&uaVariant_VendorRevision);
    UA_Variant_setScalar(&uaVariant_VendorRevision, &uaString_VendorRevision, &UA_TYPES[UA_TYPES_STRING]);
    UA_Server_writeValue(server, uaNode_VendorRevision, uaVariant_VendorRevision);
    UA_Server_writeAccessLevel(server, uaNode_VendorRevision, UA_ACCESSLEVELMASK_READ);

    //   Version
    string sEding_VendorVersion = ProLight1000.Get_CompanionSpecificationVersion();
    UA_String uaString_VendVersion = UA_STRING((char*)sEding_VendorVersion.c_str());
    UA_NodeId uaNode_VendorVersion = UA_NODEID_STRING(3, "a.s6003");
    UA_Variant uaVariant_VendorVersion;
    UA_Variant_init(&uaVariant_VendorVersion);
    UA_Variant_setScalar(&uaVariant_VendorVersion, &uaString_VendVersion, &UA_TYPES[UA_TYPES_STRING]);
    UA_Server_writeValue(server, uaNode_VendorVersion, uaVariant_VendorVersion);
    UA_Server_writeAccessLevel(server, uaNode_VendorVersion, UA_ACCESSLEVELMASK_READ);


    //   Informações Para a Instância CncChannel  ->(Ch1)<-  //
    //   Ch1 ActFeedRate
    UA_NodeId uaNode_Ch1_ActFeedRate = UA_NODEID_STRING(3, "a.s6149");
    UA_DataValue uaDataValue_Ch1_ActFeedRate;
    UA_DataValue_init(&uaDataValue_Ch1_ActFeedRate);
    uaDataValue_Ch1_ActFeedRate.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_ActFeedRate, uaDataValue_Ch1_ActFeedRate);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_ActFeedRate, UA_ACCESSLEVELMASK_READ);

    //   Ch1 ActFeedOverride
    UA_NodeId uaNode_Ch1_ActOverride = UA_NODEID_STRING(3, "a.s6161");
    UA_DataValue uaDataValue_Ch1_ActOverride;
    UA_DataValue_init(&uaDataValue_Ch1_ActOverride);
    uaDataValue_Ch1_ActOverride.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_ActOverride, uaDataValue_Ch1_ActOverride);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_ActOverride, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs A  --> ActPos <--
    UA_NodeId uaNode_Ch1_PosBcsA_Act = UA_NODEID_STRING(3, "a.s6183");
    UA_DataValue uaDataValue_Ch1_PosBcsA_Act;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsA_Act);
    uaDataValue_Ch1_PosBcsA_Act.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsA_Act, uaDataValue_Ch1_PosBcsA_Act);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsA_Act, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs A  --> CmdPos <--
    UA_NodeId uaNode_Ch1_PosBcsA_Cmd = UA_NODEID_STRING(3, "a.s6184");
    UA_DataValue uaDataValue_Ch1_PosBcsA_Cmd;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsA_Cmd);
    uaDataValue_Ch1_PosBcsA_Cmd.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsA_Cmd, uaDataValue_Ch1_PosBcsA_Cmd);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsA_Cmd, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs A  --> RemDist <--
    UA_NodeId uaNode_Ch1_PosBcsA_RemD = UA_NODEID_STRING(3, "a.s6187");
    UA_DataValue uaDataValue_Ch1_PosBcsA_RemD;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsA_RemD);
    uaDataValue_Ch1_PosBcsA_RemD.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsA_RemD, uaDataValue_Ch1_PosBcsA_RemD);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsA_RemD, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs B  --> ActPos <--
    UA_NodeId uaNode_Ch1_PosBcsB_Act = UA_NODEID_STRING(3, "a.s6189");
    UA_DataValue uaDataValue_Ch1_PosBcsB_Act;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsB_Act);
    uaDataValue_Ch1_PosBcsB_Act.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsB_Act, uaDataValue_Ch1_PosBcsB_Act);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsB_Act, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs B  --> CmdPos <--
    UA_NodeId uaNode_Ch1_PosBcsB_Cmd = UA_NODEID_STRING(3, "a.s6190");
    UA_DataValue uaDataValue_Ch1_PosBcsB_Cmd;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsB_Cmd);
    uaDataValue_Ch1_PosBcsB_Cmd.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsB_Cmd, uaDataValue_Ch1_PosBcsB_Cmd);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsB_Cmd, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs B  --> RemDist <--
    UA_NodeId uaNode_Ch1_PosBcsB_RemD = UA_NODEID_STRING(3, "a.s6193");
    UA_DataValue uaDataValue_Ch1_PosBcsB_RemD;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsB_RemD);
    uaDataValue_Ch1_PosBcsB_RemD.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsB_RemD, uaDataValue_Ch1_PosBcsB_RemD);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsB_RemD, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs C  --> ActPos <--
    UA_NodeId uaNode_Ch1_PosBcsC_Act = UA_NODEID_STRING(3, "a.s6195");
    UA_DataValue uaDataValue_Ch1_PosBcsC_Act;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsC_Act);
    uaDataValue_Ch1_PosBcsC_Act.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsC_Act, uaDataValue_Ch1_PosBcsC_Act);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsC_Act, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs C  --> CmdPos <--
    UA_NodeId uaNode_Ch1_PosBcsC_Cmd = UA_NODEID_STRING(3, "a.s6196");
    UA_DataValue uaDataValue_Ch1_PosBcsC_Cmd;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsC_Cmd);
    uaDataValue_Ch1_PosBcsC_Cmd.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsC_Cmd, uaDataValue_Ch1_PosBcsC_Cmd);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsC_Cmd, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpBcs C  --> RemDist <--
    UA_NodeId uaNode_Ch1_PosBcsC_RemD = UA_NODEID_STRING(3, "a.s6199");
    UA_DataValue uaDataValue_Ch1_PosBcsC_RemD;
    UA_DataValue_init(&uaDataValue_Ch1_PosBcsC_RemD);
    uaDataValue_Ch1_PosBcsC_RemD.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosBcsC_RemD, uaDataValue_Ch1_PosBcsC_RemD);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosBcsC_RemD, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs A  --> ActPos <--
    UA_NodeId uaNode_Ch1_PosWcsA_Act = UA_NODEID_STRING(3, "a.s6219");
    UA_DataValue uaDataValue_Ch1_PosWcsA_Act;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsA_Act);
    uaDataValue_Ch1_PosWcsA_Act.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsA_Act, uaDataValue_Ch1_PosWcsA_Act);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsA_Act, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs A  --> CmdPos <--
    UA_NodeId uaNode_Ch1_PosWcsA_Cmd = UA_NODEID_STRING(3, "a.s6220");
    UA_DataValue uaDataValue_Ch1_PosWcsA_Cmd;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsA_Cmd);
    uaDataValue_Ch1_PosWcsA_Cmd.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsA_Cmd, uaDataValue_Ch1_PosWcsA_Cmd);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsA_Cmd, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs A  --> RemDist <--
    UA_NodeId uaNode_Ch1_PosWcsA_RemD = UA_NODEID_STRING(3, "a.s6223");
    UA_DataValue uaDataValue_Ch1_PosWcsA_RemD;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsA_RemD);
    uaDataValue_Ch1_PosWcsA_RemD.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsA_RemD, uaDataValue_Ch1_PosWcsA_RemD);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsA_RemD, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs B  --> ActPos <--
    UA_NodeId uaNode_Ch1_PosWcsB_Act = UA_NODEID_STRING(3, "a.s6225");
    UA_DataValue uaDataValue_Ch1_PosWcsB_Act;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsB_Act);
    uaDataValue_Ch1_PosWcsB_Act.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsB_Act, uaDataValue_Ch1_PosWcsB_Act);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsB_Act, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs B  --> CmdPos <--
    UA_NodeId uaNode_Ch1_PosWcsB_Cmd = UA_NODEID_STRING(3, "a.s6226");
    UA_DataValue uaDataValue_Ch1_PosWcsB_Cmd;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsB_Cmd);
    uaDataValue_Ch1_PosWcsB_Cmd.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsB_Cmd, uaDataValue_Ch1_PosWcsB_Cmd);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsB_Cmd, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs B  --> RemDist <--
    UA_NodeId uaNode_Ch1_PosWcsB_RemD = UA_NODEID_STRING(3, "a.s6229");
    UA_DataValue uaDataValue_Ch1_PosWcsB_RemD;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsB_RemD);
    uaDataValue_Ch1_PosWcsB_RemD.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsB_RemD, uaDataValue_Ch1_PosWcsB_RemD);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsB_RemD, UA_ACCESSLEVELMASK_READ);

    //  Ch1 PosTcpWcs C  --> ActPos <--
    UA_NodeId uaNode_Ch1_PosWcsC_Act = UA_NODEID_STRING(3, "a.s6231");
    UA_DataValue uaDataValue_Ch1_PosWcsC_Act;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsC_Act);
    uaDataValue_Ch1_PosWcsC_Act.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsC_Act, uaDataValue_Ch1_PosWcsC_Act);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsC_Act, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs C  --> CmdPos <--
    UA_NodeId uaNode_Ch1_PosWcsC_Cmd = UA_NODEID_STRING(3, "a.s6232");
    UA_DataValue uaDataValue_Ch1_PosWcsC_Cmd;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsC_Cmd);
    uaDataValue_Ch1_PosWcsC_Cmd.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsC_Cmd, uaDataValue_Ch1_PosWcsC_Cmd);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsC_Cmd, UA_ACCESSLEVELMASK_READ);

    //   Ch1 PosTcpWcs C  --> RemDist <--
    UA_NodeId uaNode_Ch1_PosWcsC_RemD = UA_NODEID_STRING(3, "a.s6235");
    UA_DataValue uaDataValue_Ch1_PosWcsC_RemD;
    UA_DataValue_init(&uaDataValue_Ch1_PosWcsC_RemD);
    uaDataValue_Ch1_PosWcsC_RemD.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_PosWcsC_RemD, uaDataValue_Ch1_PosWcsC_RemD);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_PosWcsC_RemD, UA_ACCESSLEVELMASK_READ);

    //   Ch1 ID
    UA_NodeId uaNode_Ch1_ID = UA_NODEID_STRING(3, "a.s6181");
    UA_Variant uaVariant_Ch1_ID;
    UA_Variant_init(&uaVariant_Ch1_ID);
    UA_UInt32 uaInt32_Ch1_ID = 1;
    UA_Variant_setScalar(&uaVariant_Ch1_ID, &uaInt32_Ch1_ID, &UA_TYPES[UA_TYPES_UINT32]);
    UA_Server_writeValue(server, uaNode_Ch1_ID, uaVariant_Ch1_ID);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_ID, UA_ACCESSLEVELMASK_READ);

    //   Ch1 ActProgramFile
    UA_NodeId uaNode_Ch1_ActProgFile = UA_NODEID_STRING(3, "a.s6165");
    UA_DataValue uaDataValue_Ch1_ActProgFile;
    UA_DataValue_init(&uaDataValue_Ch1_ActProgFile);
    uaDataValue_Ch1_ActProgFile.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_ActProgFile, uaDataValue_Ch1_ActProgFile);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_ActProgFile, UA_ACCESSLEVELMASK_READ);

    //   Ch1 ActProgramName
    UA_NodeId uaNode_Ch1_ActProgName = UA_NODEID_STRING(3, "a.s6166");
    UA_DataValue uaDataValue_Ch1_ActProgName;
    UA_DataValue_init(&uaDataValue_Ch1_ActProgName);
    uaDataValue_Ch1_ActProgName.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Ch1_ActProgName, uaDataValue_Ch1_ActProgName);
    UA_Server_writeAccessLevel(server, uaNode_Ch1_ActProgName, UA_ACCESSLEVELMASK_READ);


    //   Informações Para a Instância CncAxis  ->(X1)<-  //
    //   X1 ActChannel
    UA_NodeId uaNode_X1_ActChannel = UA_NODEID_STRING(3, "a.s6050");
    UA_NodeId uaNodeID_X1_ActChannelValue = UA_NODEID_STRING(3, "a.s5009");
    UA_Variant uaVariant_X1_ActChannel;
    UA_Variant_init(&uaVariant_X1_ActChannel);
    UA_Variant_setScalar(&uaVariant_X1_ActChannel, &uaNodeID_X1_ActChannelValue, &UA_TYPES[UA_TYPES_NODEID]);
    UA_Server_writeValue(server, uaNode_X1_ActChannel, uaVariant_X1_ActChannel);
    UA_Server_writeAccessLevel(server, uaNode_X1_ActChannel, UA_ACCESSLEVELMASK_READ);

    //   X1 ActLoad
    UA_NodeId uaNode_X1_ActLoad = UA_NODEID_STRING(3, "a.s6051");
    UA_DataValue uaDataValue_X1_ActLoad;
    UA_DataValue_init(&uaDataValue_X1_ActLoad);
    uaDataValue_X1_ActLoad.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_X1_ActLoad, uaDataValue_X1_ActLoad);
    UA_Server_writeAccessLevel(server, uaNode_X1_ActLoad, UA_ACCESSLEVELMASK_READ);

    //   X1 ActPower
    UA_NodeId uaNode_X1_ActPower = UA_NODEID_STRING(3, "a.s6054");
    UA_DataValue uaDataValue_X1_ActPower;
    UA_DataValue_init(&uaDataValue_X1_ActPower);
    uaDataValue_X1_ActPower.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_X1_ActPower, uaDataValue_X1_ActPower);
    UA_Server_writeAccessLevel(server, uaNode_X1_ActPower, UA_ACCESSLEVELMASK_READ);

    //   X1 ActTorque
    UA_NodeId uaNode_X1_ActTorque = UA_NODEID_STRING(3, "a.s6058");
    UA_DataValue uaDataValue_X1_ActTorque;
    UA_DataValue_init(&uaDataValue_X1_ActTorque);
    uaDataValue_X1_ActTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_X1_ActTorque, uaDataValue_X1_ActTorque);
    UA_Server_writeAccessLevel(server, uaNode_X1_ActTorque, UA_ACCESSLEVELMASK_READ);

    //   X1 CmdTorque
    UA_NodeId uaNode_X1_CmdTorque = UA_NODEID_STRING(3, "a.s6061");
    UA_DataValue uaDataValue_X1_CmdTorque;
    UA_DataValue_init(&uaDataValue_X1_CmdTorque);
    uaDataValue_X1_CmdTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_X1_CmdTorque, uaDataValue_X1_CmdTorque);
    UA_Server_writeAccessLevel(server, uaNode_X1_CmdTorque, UA_ACCESSLEVELMASK_READ);

    //   X1 IsRotational
    bool b_X1_Rotational = false;
    UA_NodeId uaNode_X1_Rotational = UA_NODEID_STRING(3, "a.s6066");
    UA_Variant uaVariant_X1_Rotational;
    UA_Variant_setScalar(&uaVariant_X1_Rotational, &b_X1_Rotational, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_X1_Rotational, uaVariant_X1_Rotational);
    UA_Server_writeAccessLevel(server, uaNode_X1_Rotational, UA_ACCESSLEVELMASK_READ);

    //   X1 IsInactive
    bool b_X1_Inactive = false;
    UA_NodeId uaNode_X1_Inactive = UA_NODEID_STRING(3, "a.s6064");
    UA_Variant uaVariant_X1_Inactive;
    UA_Variant_setScalar(&uaVariant_X1_Inactive, &b_X1_Inactive, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_X1_Inactive, uaVariant_X1_Inactive);
    UA_Server_writeAccessLevel(server, uaNode_X1_Inactive, UA_ACCESSLEVELMASK_READ);

    //   X1 IsVirtual
    bool b_SimMode = ProLight1000.Get_SimulationMode();
    UA_NodeId uaNode_X1_Virtual = UA_NODEID_STRING(3, "a.s6067");
    UA_Variant uaVariant_X1_Virtual;
    UA_Variant_setScalar(&uaVariant_X1_Virtual, &b_SimMode, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_X1_Virtual, uaVariant_X1_Virtual);
    UA_Server_writeAccessLevel(server, uaNode_X1_Virtual, UA_ACCESSLEVELMASK_READ);


    //   Informações Para a Instância CncAxis  ->(Y1)<-  //

    //   Y1 ActChannel
    UA_NodeId uaNode_Y1_ActChannel = UA_NODEID_STRING(3, "a.s6083");
    UA_NodeId uaNode_Y1_ActChannelValue = UA_NODEID_STRING(3, "a.s5009");
    UA_Variant uaVariant_Y1_ActChannel;
    UA_Variant_init(&uaVariant_Y1_ActChannel);
    UA_Variant_setScalar(&uaVariant_Y1_ActChannel, &uaNode_Y1_ActChannelValue, &UA_TYPES[UA_TYPES_NODEID]);
    UA_Server_writeValue(server, uaNode_Y1_ActChannel, uaVariant_Y1_ActChannel);
    UA_Server_writeAccessLevel(server, uaNode_Y1_ActChannel, UA_ACCESSLEVELMASK_READ);

    //   Y1 ActLoad
    UA_NodeId uaNode_Y1_ActLoad = UA_NODEID_STRING(3, "a.s6084");
    UA_DataValue uaDataValue_Y1_ActLoad;
    UA_DataValue_init(&uaDataValue_Y1_ActLoad);
    uaDataValue_Y1_ActLoad.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Y1_ActLoad, uaDataValue_Y1_ActLoad);
    UA_Server_writeAccessLevel(server, uaNode_Y1_ActLoad, UA_ACCESSLEVELMASK_READ);

    //   Y1 ActPower
    UA_NodeId uaNode_Y1_ActPower = UA_NODEID_STRING(3, "a.s6087");
    UA_DataValue uaDataValue_Y1_ActPower;
    UA_DataValue_init(&uaDataValue_Y1_ActPower);
    uaDataValue_Y1_ActPower.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Y1_ActPower, uaDataValue_Y1_ActPower);
    UA_Server_writeAccessLevel(server, uaNode_Y1_ActPower, UA_ACCESSLEVELMASK_READ);

    //   Y1 ActTorque
    UA_NodeId uaNode_Y1_ActTorque = UA_NODEID_STRING(3, "a.s6091");
    UA_DataValue uaDataValue_Y1_ActTorque;
    UA_DataValue_init(&uaDataValue_Y1_ActTorque);
    uaDataValue_Y1_ActTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Y1_ActTorque, uaDataValue_Y1_ActTorque);
    UA_Server_writeAccessLevel(server, uaNode_Y1_ActTorque, UA_ACCESSLEVELMASK_READ);

    //   Y1 CmdTorque
    UA_NodeId uaNode_Y1_CmdTorque = UA_NODEID_STRING(3, "a.s6094");
    UA_DataValue uaDataValue_Y1_CmdTorque;
    UA_DataValue_init(&uaDataValue_Y1_CmdTorque);
    uaDataValue_Y1_CmdTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Y1_CmdTorque, uaDataValue_Y1_CmdTorque);
    UA_Server_writeAccessLevel(server, uaNode_Y1_CmdTorque, UA_ACCESSLEVELMASK_READ);

    //   Y1 IsRotational
    bool b_Y1_Rotational = false;
    UA_NodeId uaNode_Y1_Rotational = UA_NODEID_STRING(3, "a.s6099");
    UA_Variant uaVariant_Y1_Rotational;
    UA_Variant_setScalar(&uaVariant_Y1_Rotational, &b_Y1_Rotational, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_Y1_Rotational, uaVariant_Y1_Rotational);
    UA_Server_writeAccessLevel(server, uaNode_Y1_Rotational, UA_ACCESSLEVELMASK_READ);

    //   Y1 IsInactive
    bool b_Y1_Inactive = false;
    UA_NodeId uaNode_Y1_Inactive = UA_NODEID_STRING(3, "a.s6097");
    UA_Variant uaVariant_Y1_Inactive;
    UA_Variant_setScalar(&uaVariant_Y1_Inactive, &b_Y1_Inactive, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_Y1_Inactive, uaVariant_Y1_Inactive);
    UA_Server_writeAccessLevel(server, uaNode_Y1_Inactive, UA_ACCESSLEVELMASK_READ);

    //   Y1 IsVirtual
    UA_NodeId uaNode_Y1_Virtual = UA_NODEID_STRING(3, "a.s6100");
    UA_Variant uaVariant_Y1_Virtual;
    UA_Variant_setScalar(&uaVariant_Y1_Virtual, &b_SimMode, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_Y1_Virtual, uaVariant_Y1_Virtual);
    UA_Server_writeAccessLevel(server, uaNode_Y1_Virtual, UA_ACCESSLEVELMASK_READ);


    //   Informações Para a Instância CncAxis  ->(Z1)<-  //
 
    //   Z1 ActChannel
    UA_NodeId uaNode_Z1_ActChannel = UA_NODEID_STRING(3, "a.s6116");
    UA_NodeId uaNode_Z1_ActChannelValue = UA_NODEID_STRING(3, "a.s5009");
    UA_Variant uaVariant_Z1_ActChannel;
    UA_Variant_init(&uaVariant_Z1_ActChannel);
    UA_Variant_setScalar(&uaVariant_Z1_ActChannel, &uaNode_Z1_ActChannelValue, &UA_TYPES[UA_TYPES_NODEID]);
    UA_Server_writeValue(server, uaNode_Z1_ActChannel, uaVariant_Z1_ActChannel);
    UA_Server_writeAccessLevel(server, uaNode_Z1_ActChannel, UA_ACCESSLEVELMASK_READ);

    //   Z1 ActLoad
    UA_NodeId uaNode_Z1_ActLoad = UA_NODEID_STRING(3, "a.s6117");
    UA_DataValue uaDataValue_Z1_ActLoad;
    UA_DataValue_init(&uaDataValue_Z1_ActLoad);
    uaDataValue_Z1_ActLoad.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Z1_ActLoad, uaDataValue_Z1_ActLoad);
    UA_Server_writeAccessLevel(server, uaNode_Z1_ActLoad, UA_ACCESSLEVELMASK_READ);

    //   Z1 ActPower
    UA_NodeId uaNode_Z1_ActPower = UA_NODEID_STRING(3, "a.s6120");
    UA_DataValue uaDataValue_Z1_ActPower;
    UA_DataValue_init(&uaDataValue_Z1_ActPower);
    uaDataValue_Z1_ActPower.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Z1_ActPower, uaDataValue_Z1_ActPower);
    UA_Server_writeAccessLevel(server, uaNode_Z1_ActPower, UA_ACCESSLEVELMASK_READ);

    //   Z1 ActTorque
    UA_NodeId uaNode_Z1_ActTorque = UA_NODEID_STRING(3, "a.s6124");
    UA_DataValue uaDataValue_Z1_ActTorque;
    UA_DataValue_init(&uaDataValue_Z1_ActTorque);
    uaDataValue_Z1_ActTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Z1_ActTorque, uaDataValue_Z1_ActTorque);
    UA_Server_writeAccessLevel(server, uaNode_Z1_ActTorque, UA_ACCESSLEVELMASK_READ);

    //   Z1 CmdTorque
    UA_NodeId uaNode_Z1_CmdTorque = UA_NODEID_STRING(3, "a.s6127");
    UA_DataValue uaDataValue_Z1_CmdTorque;
    UA_DataValue_init(&uaDataValue_Z1_CmdTorque);
    uaDataValue_Z1_CmdTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_Z1_CmdTorque, uaDataValue_Z1_CmdTorque);
    UA_Server_writeAccessLevel(server, uaNode_Z1_CmdTorque, UA_ACCESSLEVELMASK_READ);

    //   Z1 IsRotational
    bool b_Z1_Rotational = false;
    UA_NodeId uaNode_Z1_Rotational = UA_NODEID_STRING(3, "a.s6132");
    UA_Variant uaVariant_Z1_Rotational;
    UA_Variant_setScalar(&uaVariant_Z1_Rotational, &b_Z1_Rotational, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_Z1_Rotational, uaVariant_Z1_Rotational);
    UA_Server_writeAccessLevel(server, uaNode_Z1_Rotational, UA_ACCESSLEVELMASK_READ);

    //   Z1 IsInactive
    bool b_Z1_Inactive = false;
    UA_NodeId uaNode_Z1_Inactive = UA_NODEID_STRING(3, "a.s6130");
    UA_Variant uaVariant_Z1_Inactive;
    UA_Variant_setScalar(&uaVariant_Z1_Inactive, &b_Z1_Inactive, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_Z1_Inactive, uaVariant_Z1_Inactive);
    UA_Server_writeAccessLevel(server, uaNode_Z1_Inactive, UA_ACCESSLEVELMASK_READ);

    //   Z1 IsVirtual
    UA_NodeId uaNode_Z1_Virtual = UA_NODEID_STRING(3, "a.s6133");
    UA_Variant uaVariant_Z1_Virtual;
    UA_Variant_setScalar(&uaVariant_Z1_Virtual, &b_SimMode, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_Z1_Virtual, uaVariant_Z1_Virtual);
    UA_Server_writeAccessLevel(server, uaNode_Z1_Virtual, UA_ACCESSLEVELMASK_READ);


    //   Informações Para a Instância CncSpindle  ->(S1)<-  //

    //   S1 ActChannel
    UA_NodeId uaNode_S1_ActChannel = UA_NODEID_STRING(3, "a.s6341");
    UA_NodeId uaNode_S1_ActChannelValue = UA_NODEID_STRING(3, "a.s5009");
    UA_Variant uaVariant_S1_ActChannel;
    UA_Variant_init(&uaVariant_S1_ActChannel);
    UA_Variant_setScalar(&uaVariant_S1_ActChannel, &uaNode_S1_ActChannelValue, &UA_TYPES[UA_TYPES_NODEID]);
    UA_Server_writeValue(server, uaNode_S1_ActChannel, uaVariant_S1_ActChannel);
    UA_Server_writeAccessLevel(server, uaNode_S1_ActChannel, UA_ACCESSLEVELMASK_READ);

    //   S1 ActLoad
    UA_NodeId uaNode_S1_ActLoad = UA_NODEID_STRING(3, "a.s6342");
    UA_DataValue uaDataValue_S1_ActLoad;
    UA_DataValue_init(&uaDataValue_S1_ActLoad);
    uaDataValue_S1_ActLoad.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_ActLoad, uaDataValue_S1_ActLoad);
    UA_Server_writeAccessLevel(server, uaNode_S1_ActLoad, UA_ACCESSLEVELMASK_READ);

    //   S1 ActOverride
    UA_NodeId uaNode_S1_ActOverride = UA_NODEID_STRING(3, "a.s6322");
    UA_DataValue uaDataValue_S1_ActOverride;
    UA_DataValue_init(&uaDataValue_S1_ActOverride);
    uaDataValue_S1_ActOverride.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_ActOverride, uaDataValue_S1_ActOverride);
    UA_Server_writeAccessLevel(server, uaNode_S1_ActOverride, UA_ACCESSLEVELMASK_READ);

    //   S1 ActPower
    UA_NodeId uaNode_S1_ActPower = UA_NODEID_STRING(3, "a.s6345");
    UA_DataValue uaDataValue_S1_ActPower;
    UA_DataValue_init(&uaDataValue_S1_ActPower);
    uaDataValue_S1_ActPower.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_ActPower, uaDataValue_S1_ActPower);
    UA_Server_writeAccessLevel(server, uaNode_S1_ActPower, UA_ACCESSLEVELMASK_READ);

    //   S1 ActSpeed
    UA_NodeId uaNode_S1_ActSpeed = UA_NODEID_STRING(3, "a.s6324");
    UA_DataValue uaDataValue_S1_ActSpeed;
    UA_DataValue_init(&uaDataValue_S1_ActSpeed);
    uaDataValue_S1_ActSpeed.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_ActSpeed, uaDataValue_S1_ActSpeed);
    UA_Server_writeAccessLevel(server, uaNode_S1_ActSpeed, UA_ACCESSLEVELMASK_READ);

    //   S1 ActTorque
    UA_NodeId uaNode_S1_ActTorque = UA_NODEID_STRING(3, "a.s6348");    
    UA_DataValue uaDataValue_S1_ActTorque;
    UA_DataValue_init(&uaDataValue_S1_ActTorque);
    uaDataValue_S1_ActTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_ActTorque, uaDataValue_S1_ActTorque);
    UA_Server_writeAccessLevel(server, uaNode_S1_ActTorque, UA_ACCESSLEVELMASK_READ);

    //   S1 CmdTorque
    UA_NodeId uaNode_S1_CmdTorque = UA_NODEID_STRING(3, "a.s6351");
    UA_DataValue uaDataValue_S1_CmdTorque;
    UA_DataValue_init(&uaDataValue_S1_CmdTorque);
    uaDataValue_S1_CmdTorque.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_CmdTorque, uaDataValue_S1_CmdTorque);
    UA_Server_writeAccessLevel(server, uaNode_S1_CmdTorque, UA_ACCESSLEVELMASK_READ);

    //   S1 ActGear
    UA_NodeId uaNode_S1_ActGear = UA_NODEID_STRING(3, "a.s6321");
    UA_Variant uaVariant_S1_ActGear;
    UA_Variant_init(&uaVariant_S1_ActGear);
    UA_UInt32 uaInt32_S1_ActGear = 1;
    UA_Variant_setScalar(&uaVariant_S1_ActGear, &uaInt32_S1_ActGear, &UA_TYPES[UA_TYPES_UINT32]);
    UA_Server_writeValue(server, uaNode_S1_ActGear, uaVariant_S1_ActGear);
    UA_Server_writeAccessLevel(server, uaNode_S1_ActGear, UA_ACCESSLEVELMASK_READ);

    //   S1 CmdGear
    UA_NodeId uaNode_S1_CmdGear = UA_NODEID_STRING(3, "a.s6335");
    UA_Variant uaVariant_S1_CmdGear;
    UA_Variant_init(&uaVariant_S1_CmdGear);
    UA_UInt32 uaInt32_S1_CmdGear = 1;
    UA_Variant_setScalar(&uaVariant_S1_CmdGear, &uaInt32_S1_CmdGear, &UA_TYPES[UA_TYPES_UINT32]);
    UA_Server_writeValue(server, uaNode_S1_CmdGear, uaVariant_S1_CmdGear);
    UA_Server_writeAccessLevel(server, uaNode_S1_CmdGear, UA_ACCESSLEVELMASK_READ);

    //   S1 AnglePos  --> ActPos <--
    UA_NodeId uaNode_S1_AnglePos_Act = UA_NODEID_STRING(3, "a.s6330");
    UA_DataValue uaDataValue_S1_AnglePos_Act;
    UA_DataValue_init(&uaDataValue_S1_AnglePos_Act);
    uaDataValue_S1_AnglePos_Act.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_AnglePos_Act, uaDataValue_S1_AnglePos_Act);
    UA_Server_writeAccessLevel(server, uaNode_S1_AnglePos_Act, UA_ACCESSLEVELMASK_READ);

    //   S1 AnglePos  --> CmdPos <--
    UA_NodeId uaNode_S1_AnglePos_Cmd = UA_NODEID_STRING(3, "a.s6331");
    UA_DataValue uaDataValue_S1_AnglePos_Cmd;
    UA_DataValue_init(&uaDataValue_S1_AnglePos_Cmd);
    uaDataValue_S1_AnglePos_Cmd.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_AnglePos_Cmd, uaDataValue_S1_AnglePos_Cmd);
    UA_Server_writeAccessLevel(server, uaNode_S1_AnglePos_Cmd, UA_ACCESSLEVELMASK_READ);

    //   S1 AnglePos  --> RemDist <--
    UA_NodeId uaNode_S1_AnglePos_RemD = UA_NODEID_STRING(3, "a.s6334");
    UA_DataValue uaDataValue_S1_AnglePos_RemD;
    UA_DataValue_init(&uaDataValue_S1_AnglePos_RemD);
    uaDataValue_S1_AnglePos_RemD.hasValue = false;
    UA_Server_writeDataValue(server, uaNode_S1_AnglePos_RemD, uaDataValue_S1_AnglePos_RemD);
    UA_Server_writeAccessLevel(server, uaNode_S1_AnglePos_RemD, UA_ACCESSLEVELMASK_READ);

    //   S1 IsVirtual
    UA_NodeId uaNode_S1_Virtual = UA_NODEID_STRING(3, "a.s6355");    
    UA_Variant uaVariant_S1_Virtual;
    UA_Variant_setScalar(&uaVariant_S1_Virtual, &b_SimMode, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Server_writeValue(server, uaNode_S1_Virtual, uaVariant_S1_Virtual);
    UA_Server_writeAccessLevel(server, uaNode_S1_Virtual, UA_ACCESSLEVELMASK_READ);
};


string buffer = " ";
int    ch1_ActProgStatus = 2;

static void periodicUpdateValues(UA_Server* server, void* data) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "PeriodicUpdate");
    
    CNC_Eding ProLight1000;
    ValueElementFunction_GenericCncClass trueElemGenFunStruct;
    vector<ValueElementFunction_GenericCncClass> vFunTrueElemsStruct;
    vector<ElementFunction_GenericCncClass> vectKV_TrueElemFunct;

    // ---------------------------------------------------------------------------- //
    //  Below the Values of Objects are assigned accordingly the CNCBase Functions  //
    //  These Objects are periodicly updated by the periodicUpdateValues Callback   //

    //  Ch1 ActGFunctions
    string sActGFunctions = ProLight1000.Get_ActGFunctions();
    istringstream ss_I(sActGFunctions);
    vector<string> vectStrg_C1ActGFunctions;
    string del_I;
    while (getline(ss_I, del_I, ' ')) {
      if (del_I.length() > 1) {
        del_I.erase(0, 1);
        vectStrg_C1ActGFunctions.push_back(del_I);
      };
    };
    UA_Int32* ch1_ActGFunction = new UA_Int32[vectStrg_C1ActGFunctions.size()];
    for (int i = 0; i < vectStrg_C1ActGFunctions.size(); i++) {
      ch1_ActGFunction[i] = stoi(vectStrg_C1ActGFunctions[i]);
    };

    //  Ch1 ActMFunctions
    string sActMFunctions = ProLight1000.Get_ActMFunctions();
    istringstream ss_II(sActMFunctions);
    vector<string> vectStrg_C1ActMFunctions;
    string del_II;
    while (getline(ss_II, del_II, ' ')) {
      if (del_II.length() > 1) {
        del_II.erase(0, 1);
        vectStrg_C1ActMFunctions.push_back(del_II);
      };
    };
    UA_Int32* ch1_ActMFunction = new UA_Int32[vectStrg_C1ActMFunctions.size()];
    for (int j = 0; j < vectStrg_C1ActMFunctions.size(); j++) {
      ch1_ActMFunction[j] = stoi(vectStrg_C1ActMFunctions[j]);
    };

    //  Ch1 ActModalOffset
    istringstream ss_III(sActGFunctions);
    vector<string> vectStrg_C1ModalOffsetFunctions;
    string del_III;
    while (getline(ss_III, del_III, ' ')) {
      if (del_III == "G54" || del_III == "G55" || del_III == "G56" || del_III == "G57" || del_III == "G58"
         || del_III == "G59" || del_III == "G59.1" || del_III == "G59.2" || del_III == "G59.3") {
        del_III.erase(0, 1);
        vectStrg_C1ModalOffsetFunctions.push_back(del_III);
      };
    };

    UA_String* vectUaString_CInterpreterBlockText = new UA_String[3];
    string ch1_CInterpreterLineText = ProLight1000.CurrentILineText();
    // string ch1_InterpreterNextLine = ProLight1000.InterpreterNextLineText();
    vectUaString_CInterpreterBlockText[0] = UA_STRING((char*)buffer.c_str());
    vectUaString_CInterpreterBlockText[1] = UA_STRING((char*)ch1_CInterpreterLineText.c_str());
    // vectUaString_CInterpreterBlockText[2] = UA_STRING((char*)ch1_InterpreterNextLine.c_str());
    vectUaString_CInterpreterBlockText[2] = UA_STRING(" ");

    int    ch1_ActModalOffset = stoi(vectStrg_C1ModalOffsetFunctions.back());
    double ch1_BcsActPosX = ProLight1000.Get_tcp_bcs_x_actpos();
    double ch1_BcsActPosY = ProLight1000.Get_tcp_bcs_y_actpos();
    double ch1_BcsActPosZ = ProLight1000.Get_tcp_bcs_z_actpos();
    bool   ch1_BlockMode = ProLight1000.Get_SingleStepMode();
    double ch1_CmdFeed = ProLight1000.Get_S1_ProgrammedFeed();
    double ch1_CmdFeedOverride = ProLight1000.Get_S1_CmdFeedOverride();
    int    ch1_CncState = ProLight1000.Get_ChannelActStatus();
    int    ch1_ToolIDinSpindle = ProLight1000.Get_ToolIDinSpindle();
    double ch1_WcsActPosX = ProLight1000.Get_tcp_wcs_x_actpos();
    double ch1_WcsActPosY = ProLight1000.Get_tcp_wcs_y_actpos();
    double ch1_WcsActPosZ = ProLight1000.Get_tcp_wcs_z_actpos();

    string sActMainProgFile = ProLight1000.Get_act_main_program_file();
    UA_String uaStringActMainProgFile = UA_STRING((char*)sActMainProgFile.c_str());

    istringstream ssIII(sActMainProgFile);
    vector<string> vectStrg_MainFunctName;
    string delIII;
    while (getline(ssIII, delIII, '\\')) {
      vectStrg_MainFunctName.push_back(delIII);
    };
    string ch1_MainProgName = vectStrg_MainFunctName.back();
    UA_String uaStringActMainProgName = UA_STRING((char*)ch1_MainProgName.c_str());

    int    ch1_CncStatusEnum = CncGetState();
    int    ch1_CmdOperationMode;
    int    ch1_ActOperationMode;

    int    x1_StatusEnum = CncGetJointStatus(0)->state;
    int    x1_ActStatus;
    bool   x1_Referenced = ProLight1000.CheckJointHomed(0);
    double x1_ZeroOffset = ProLight1000.Get_MachineOriginXOffset();

    int    y1_StatusEnum = CncGetJointStatus(1)->state;
    int    y1_ActStatus;
    bool   y1_Referenced = ProLight1000.CheckJointHomed(1);
    double y1_ZeroOffset = ProLight1000.Get_MachineOriginYOffset();

    int    z1_StatusEnum = CncGetJointStatus(2)->state;
    int    z1_ActStatus;
    bool   z1_Referenced = ProLight1000.CheckJointHomed(2);
    double z1_ZeroOffset = ProLight1000.Get_MachineOriginZOffset();

    double s1_CmdSpeed = ProLight1000.Get_S1_ProgrammedSpeed();
    double s1_CmdSpeedOverride = ProLight1000.Get_S1_CmdSpeedOverride();
    int    s1_ActTurnD = ProLight1000.Get_S1_TurnDirection();
    //  End of Assigning Values to the Objects to be periodically updated  //
    //  ------------------------------------------------------------------ //

    VectFunctions_GenericCncClass *instanciaVectFunct_GCC_lido_II =
     (VectFunctions_GenericCncClass*)(data);

    for (int i = 10; i < int ( (*instanciaVectFunct_GCC_lido_II).vectFunctions_GCC.size() ); i++) {

      ElementFunction_GenericCncClass elemGenFun = (*instanciaVectFunct_GCC_lido_II).vectFunctions_GCC[i];
      string key = elemGenFun.xmlKey;
      string value = elemGenFun.xmlValue;

      // Selecionar apenas as linhas que contêm "Get" e "true".
      if ((key.find("Get") != string::npos) && (value.find("true") != string::npos)) {
        vectKV_TrueElemFunct.push_back(elemGenFun);

        stringstream ss(value);
        string xmlValue_SubItem;
        vector<std::string> output;
        while (std::getline(ss, xmlValue_SubItem, ',')) {
          output.push_back(xmlValue_SubItem);
        };

        UA_Variant scUAVariantValue;
        UA_NodeId scUACurrentNodeId;

        string  sUaNodeId_FunctionElemTrue = output[0];
        int     sc_IdFunctionElemTrue = stoi(sUaNodeId_FunctionElemTrue);

        switch (sc_IdFunctionElemTrue) {
          //   Informações Para a Instância de CncAxisType ->(X1)<-  //

          //   X1 ActStatus
          case 6057:                    
               if (x1_StatusEnum == 1) {
                 x1_ActStatus = 1;
               }
               else {
                 if (x1_StatusEnum == 2) {
                   x1_ActStatus = 0;
                 };
               };
               UA_Variant_setScalar(&scUAVariantValue, &x1_ActStatus, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6057");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6057"), UA_ACCESSLEVELMASK_READ);
               break;

          //   X1 IsReferenced  (> Foi Feito o HOME ? <)
          case 6065:
               UA_Variant_setScalar(&scUAVariantValue, &x1_Referenced, &UA_TYPES[UA_TYPES_BOOLEAN]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6065");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6065"), UA_ACCESSLEVELMASK_READ);
               break;

          //   X1 PosDirect
          //   Convencionou-se PosDirect e PosIndirect iguais, e equivalentes às Coordenadas Zero-Peça
          case 6069:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosX, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6069");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6069"), UA_ACCESSLEVELMASK_READ);
               break;

          //   X1 PosIndirect
          case 6075:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosX, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6075");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6075"), UA_ACCESSLEVELMASK_READ);
               break;

          //   X1 ZeroOffset
          //   Offset definido para o Programa de Maquinação (em relação ao Zero-Máquina)
          case 6080:
               UA_Variant_setScalar(&scUAVariantValue, &x1_ZeroOffset, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6080");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6080"), UA_ACCESSLEVELMASK_READ);
               break;


          //   Informações Para a Instância de CncAxisType ->(Y1)<-  //
          
          //   Y1 ActStatus
          case 6090:
               if (y1_StatusEnum == 1) {
                 y1_ActStatus = 1;
               }
               else {
                 if (y1_StatusEnum == 2) {
                   y1_ActStatus = 0;
                 };
               };
               UA_Variant_setScalar(&scUAVariantValue, &y1_ActStatus, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6090");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6090"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Y1 IsReferenced  (> Foi Feito o HOME ? <)
          case 6098:
               UA_Variant_setScalar(&scUAVariantValue, &y1_Referenced, &UA_TYPES[UA_TYPES_BOOLEAN]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6098");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6098"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Convencionou-se PosDirect e PosIndirect iguais, e equivalentes às Coordenadas Zero-Peça
          //   Y1 PosDirect
          case 6102:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosY, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6102");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6102"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Y1 PosIndirect
          case 6108:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosY, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6108");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6108"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Y1 ZeroOffset
          //   Offset definido para o Programa de Maquinação (em relação ao Zero-Máquina)
          case 6113:
               UA_Variant_setScalar(&scUAVariantValue, &y1_ZeroOffset, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6113");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6113"), UA_ACCESSLEVELMASK_READ);
               break;


          //   Informações Para a Instância de CncAxisType ->(Z1)<-  //

          //   Z1 ActStatus
          case 6123:
               if (z1_StatusEnum == 1) {
                 z1_ActStatus = 1;
               }
               else {
                 if (z1_StatusEnum == 2) {
                   z1_ActStatus = 0;
                 };
               };
               UA_Variant_setScalar(&scUAVariantValue, &z1_ActStatus, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6123");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6123"), UA_ACCESSLEVELMASK_READ);
               break;

          ///  Z1 IsReferenced  (> Foi Feito o HOME ? <)
          case 6131:
               UA_Variant_setScalar(&scUAVariantValue, &z1_Referenced, &UA_TYPES[UA_TYPES_BOOLEAN]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6131");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6131"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Z1 PosDirect
          //   Convencionou-se PosDirect e PosIndirect iguais, e equivalentes às Coordenadas Zero-Peça
          case 6135:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosZ, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6135");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6135"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Z1 PosIndirect
          case 6141:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosZ, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6141");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6141"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Z1 ZeroOffset
          //   Offset definido para o Programa de Maquinação (em relação ao Zero-Máquina)
          case 6146:
               UA_Variant_setScalar(&scUAVariantValue, &z1_ZeroOffset, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6146");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6146"), UA_ACCESSLEVELMASK_READ);
               break;


          //   Informações Para a Instância de CncChannelType ->(Ch1)<-  //

          //   Ch1 ActGFunctions
          case 6152:
               UA_Variant_setArray(&scUAVariantValue, ch1_ActGFunction, vectStrg_C1ActGFunctions.size(),
                &UA_TYPES[UA_TYPES_UINT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6152");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6152"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ActMFunctions
          case 6158:
               UA_Variant_setArray(&scUAVariantValue, ch1_ActMFunction, vectStrg_C1ActMFunctions.size(),
                &UA_TYPES[UA_TYPES_UINT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6158");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6158"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ActMainProgramFile
          case 6156:
               UA_Variant_setScalar(&scUAVariantValue, &uaStringActMainProgFile, &UA_TYPES[UA_TYPES_STRING]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6156");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6156"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ActMainProgramName
          case 6157:
               UA_Variant_setScalar(&scUAVariantValue, &uaStringActMainProgName, &UA_TYPES[UA_TYPES_STRING]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6157");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6157"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ActProgramBlock
          case 6164:
               if (ch1_CInterpreterLineText.compare(buffer) != 0) {
                 UA_Variant_setArray(&scUAVariantValue, vectUaString_CInterpreterBlockText, 3,
                  &UA_TYPES[UA_TYPES_STRING]);                 
                 scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6164");
                 UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
                 UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6164"), UA_ACCESSLEVELMASK_READ);
                 buffer = ch1_CInterpreterLineText;
                 // UA_String_clear(vectUaString_CInterpreterBlockText);                         
                 // UA_Array_delete(vectUaString_CInterpreterBlockText, 3, &UA_TYPES[UA_TYPES_STRING]);
               };
               break;

          //   Ch1 ActOperationMode
          case 6160:
               if (ch1_CncStatusEnum == 6 || ch1_CncStatusEnum == 7) {
                 ch1_ActOperationMode = 2;
               }
               else {
                 ch1_ActOperationMode = 0;
               };
               UA_Variant_setScalar(&scUAVariantValue, &ch1_ActOperationMode, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6160");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6160"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ActProgramStatus
          case 6167:
               switch (ch1_CncStatusEnum) {
                 case 3:
                      ch1_ActProgStatus = 4;
                      break;
                 case 4:
                      ch1_ActProgStatus = 4;
                      break;

                 case 5:
                      ch1_ActProgStatus = 3;
                      break;

                 case 6:
                      ch1_ActProgStatus = 1;
                      break;
                 case 7:
                      ch1_ActProgStatus = 1;
                      break;
                 case 8:
                      ch1_ActProgStatus = 1;
                      break;
                 case 9:
                      ch1_ActProgStatus = 1;
                      break;
                 case 10:
                      ch1_ActProgStatus = 1;
                      break;

                 case 11:
                      ch1_ActProgStatus = 0;
                      break;
                 case 12:
                      ch1_ActProgStatus = 0;
                      break;
                 case 13:
                      ch1_ActProgStatus = 0;
                      break;
                 case 14:
                      ch1_ActProgStatus = 0;
                      break;
                 case 15:
                      ch1_ActProgStatus = 0;
                      break;
               };
               UA_Variant_setScalar(&scUAVariantValue, &ch1_ActProgStatus, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6167");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6167"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ActModalOffsetFunction
          case 6159:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_ActModalOffset, &UA_TYPES[UA_TYPES_UINT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6159");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6159"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 BlockMode
          case 6169:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_BlockMode, &UA_TYPES[UA_TYPES_BOOLEAN]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6169");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6169"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 CmdFeedRate
          case 6170:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_CmdFeed, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6170");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6170"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 CmdOperationMode
          case 6173:
               if (ch1_CncStatusEnum == 6 || ch1_CncStatusEnum == 7) {
                 ch1_CmdOperationMode = 2;
               }
               else {
                 ch1_CmdOperationMode = 0;
               };
               UA_Variant_setScalar(&scUAVariantValue, &ch1_CmdOperationMode, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6173");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6173"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 Cmd(Feed)Override
          case 6174:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_CmdFeedOverride, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6174");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6174"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 PosTcpWcsX
          //   valor de X [ em coordenadas Zero-Peça ]
          case 6237:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosX, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6237");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6237"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 PosTcpWcsY
          //   valor de Y [ em coordenadas Zero-Peça ]
          case 6243:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosY, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6243");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6243"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 PosTcpWcsZ
          //   valor de Z [ em coordenadas Zero-Peça ]
          case 6249:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_WcsActPosZ, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6249");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6249"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 PosTcpBcsX
          //   valor de X [ em coordenadas Zero-Máquina ]
          case 6201:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_BcsActPosX, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6201");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6201"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 PosTcpBcsY
          //   valor de Y [ em coordenadas Zero-Máquina ]
          case 6207:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_BcsActPosY, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6207");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6207"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 PosTcpBcsZ
          //   valor de Z [ em coordenadas Zero-Máquina ]
          case 6213:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_BcsActPosZ, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6213");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6213"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ToolId
          //   Ferramenta presente no Spindle
          case 6254:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_ToolIDinSpindle, &UA_TYPES[UA_TYPES_UINT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6254");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6254"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Ch1 ActStatus
          case 6168:
               UA_Variant_setScalar(&scUAVariantValue, &ch1_CncState, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6168");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6168"), UA_ACCESSLEVELMASK_READ);
               break;

          //   Informações Para a Instância de CncSpindleType ->(S1)<-  //

          //   S1 ActTurnDirection
          case 6328:
               UA_Variant_setScalar(&scUAVariantValue, &s1_ActTurnD, &UA_TYPES[UA_TYPES_INT32]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6328");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6328"), UA_ACCESSLEVELMASK_READ);
               break;

          //   S1 Cmd(Speed)Override
          case 6336:
               UA_Variant_setScalar(&scUAVariantValue, &s1_CmdSpeedOverride, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6336");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6336"), UA_ACCESSLEVELMASK_READ);
               break;

          //   S1 CmdSpeed
          case 6338:
               UA_Variant_setScalar(&scUAVariantValue, &s1_CmdSpeed, &UA_TYPES[UA_TYPES_DOUBLE]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6338");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6338"), UA_ACCESSLEVELMASK_READ);
               break;

          //   S1 IsInactive
          case 6354:
               int i_S1_On = CncGetSpindleStatus()->spindleIsOn;
               bool b_S1_Inactive;
               if (i_S1_On == 1) {
                 b_S1_Inactive = false;
               }
               else {
                 if (i_S1_On == 0) {
                   b_S1_Inactive = true;
                 };
               };
               UA_Variant_setScalar(&scUAVariantValue, &b_S1_Inactive, &UA_TYPES[UA_TYPES_BOOLEAN]);
               scUACurrentNodeId = UA_NODEID_STRING(3, "a.s6354");
               UA_Server_writeValue(server, scUACurrentNodeId, scUAVariantValue);
               UA_Server_writeAccessLevel(server, UA_NODEID_STRING(3, "a.s6354"), UA_ACCESSLEVELMASK_READ);
               break;
        };
      };
    };
};


static UA_StatusCode resetCallBack(UA_Server* server, const UA_NodeId* sessionId, void* sessionHandle,
 const UA_NodeId* methodId, void* methodContext, const UA_NodeId* objectId, void* objectContext,
 size_t inputSize, const UA_Variant* input, size_t outputSize, UA_Variant* output) {

    int statusCodeReset = ProLight1000.Reset();
    if (statusCodeReset == 0) {
      return UA_STATUSCODE_GOOD;
    }
    else {
      return UA_STATUSCODE_BAD;
    };
};

static void ResetMethod(UA_Server* server) {

    UA_MethodAttributes resetAttr = UA_MethodAttributes_default;
    resetAttr.description = UA_LOCALIZEDTEXT("pt_PT", "RESET");
    resetAttr.displayName = UA_LOCALIZEDTEXT("pt-PT", "RESET");
    resetAttr.executable = true;
    resetAttr.userExecutable = true;

    UA_Server_addMethodNode(server, UA_NODEID_STRING(3, "a.s7007"), UA_NODEID_STRING(3, "a.s5009"),
     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(3, "RESET"), resetAttr,
     &resetCallBack, 0, NULL, 0, NULL, NULL, NULL);
};


static UA_StatusCode loadJobCallBack(UA_Server* server, const UA_NodeId* sessionId, void* sessionHandle,
 const UA_NodeId* methodId, void* methodContext, const UA_NodeId* objectId, void* objectContext,
 size_t inputSize, const UA_Variant* input, size_t outputSize, UA_Variant* output) {

    UA_String* inputStr = (UA_String*)input->data;
    if (inputStr->length > 0) {

      string teste = std::string((const char*)inputStr->data, inputStr->length);
      std::wstring widestr = std::wstring(teste.begin(), teste.end());

      int statusCodeLoadJob = ProLight1000.LoadJob(widestr.c_str());
      if (statusCodeLoadJob == 0) {

        int statusCodeRenderGraphJob = ProLight1000.RenderGraph(0, 1);
        if (statusCodeRenderGraphJob == 0) {
          return UA_STATUSCODE_GOOD;
        };
      }
      else {
        return UA_STATUSCODE_BAD;
      };
    };
};

static void LoadJobMethod(UA_Server* server) {

    UA_Argument inputLoadJob;
    UA_Argument_init(&inputLoadJob);
    inputLoadJob.description = UA_LOCALIZEDTEXT("en-US", "File Directory");
    inputLoadJob.name = UA_STRING("File Directory");
    inputLoadJob.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputLoadJob.valueRank = UA_VALUERANK_SCALAR;
    
    UA_MethodAttributes loadJobAttr = UA_MethodAttributes_default;
    loadJobAttr.description = UA_LOCALIZEDTEXT("pt_PT", "Importar Programa");
    loadJobAttr.displayName = UA_LOCALIZEDTEXT("pt-PT", "Importar Programa");
    loadJobAttr.executable = true;
    loadJobAttr.userExecutable = true;

    UA_Server_addMethodNode(server, UA_NODEID_STRING(3, "a.s7005"), UA_NODEID_STRING(3, "a.s5009"),
     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(3, "Load Job"), loadJobAttr,
     &loadJobCallBack, 1, &inputLoadJob, 0, NULL, NULL, NULL);
};


static UA_StatusCode pauseJobCallBack(UA_Server* server, const UA_NodeId* sessionId, void* sessionHandle,
 const UA_NodeId* methodId, void* methodContext, const UA_NodeId* objectId, void* objectContext,
 size_t inputSize, const UA_Variant* input, size_t outputSize, UA_Variant* output) {

    int statusCodePauseJob = ProLight1000.PauseJob();
    if (statusCodePauseJob == 0) {
      return UA_STATUSCODE_GOOD;
    }
    else {
      return UA_STATUSCODE_BAD;
    };
};

static void PauseJobMethod(UA_Server* server) {

    UA_MethodAttributes pauseAttr = UA_MethodAttributes_default;
    pauseAttr.description = UA_LOCALIZEDTEXT("pt-PT", "Pausar Programa");
    pauseAttr.displayName = UA_LOCALIZEDTEXT("pt-PT", "Pausar Programa");
    pauseAttr.executable = true;
    pauseAttr.userExecutable = true;

    UA_Server_addMethodNode(server, UA_NODEID_STRING(3, "a.s7006"), UA_NODEID_STRING(3, "a.s5009"),
     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(3, "Pause Program"), pauseAttr,
     &pauseJobCallBack, 0, NULL, 0, NULL, NULL, NULL);
};


static UA_StatusCode runResumeJobCallBack(UA_Server* server, const UA_NodeId* sessionId,
 void* sessionHandle, const UA_NodeId* methodId, void* methodContext, const UA_NodeId* objectId,
 void* objectContext, size_t inputSize, const UA_Variant* input, size_t outputSize, UA_Variant* output) {

    int statusCodeRunResumeJob = ProLight1000.RunOrResumeJob();
    if (statusCodeRunResumeJob == 0) {
      return UA_STATUSCODE_GOOD;
    }
    else {
      return UA_STATUSCODE_BAD;
    };    
};

static void RunOrResumeJobMethod(UA_Server* server) {

    UA_MethodAttributes runresumeJobAttr = UA_MethodAttributes_default;
    runresumeJobAttr.description = UA_LOCALIZEDTEXT("pt_PT", "Iniciar/Continuar Programa");
    runresumeJobAttr.displayName = UA_LOCALIZEDTEXT("pt-PT", "Iniciar/Continuar Programa");
    runresumeJobAttr.executable = true;
    runresumeJobAttr.userExecutable = true;

    UA_Server_addMethodNode(server, UA_NODEID_STRING(3, "a.s7009"), UA_NODEID_STRING(3, "a.s5009"),
     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(3, "Run/Resume Job"), runresumeJobAttr,
     &runResumeJobCallBack, 0, NULL, 0, NULL, NULL, NULL);
};


static UA_StatusCode rewindJobCallBack(UA_Server* server, const UA_NodeId* sessionId, void* sessionHandle,
 const UA_NodeId* methodId, void* methodContext, const UA_NodeId* objectId, void* objectContext,
 size_t inputSize, const UA_Variant* input, size_t outputSize, UA_Variant* output) {

    int statusCodeRewindJob = ProLight1000.RewindJob();
    if (statusCodeRewindJob == 0) {
      return UA_STATUSCODE_GOOD;
    }
    else {
      return UA_STATUSCODE_BAD;
    };
};

static void RewindJobMethod(UA_Server* server) {

    UA_MethodAttributes rewindJobAttr = UA_MethodAttributes_default;
    rewindJobAttr.description = UA_LOCALIZEDTEXT("pt_PT", "Recomecar Programa");
    rewindJobAttr.displayName = UA_LOCALIZEDTEXT("pt-PT", "Recomecar Programa");
    rewindJobAttr.executable = true;
    rewindJobAttr.userExecutable = true;

    UA_Server_addMethodNode(server, UA_NODEID_STRING(3, "a.s7008"), UA_NODEID_STRING(3, "a.s5009"),
     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(3, "Rewind Program"), rewindJobAttr,
     &rewindJobCallBack, 0, NULL, 0, NULL, NULL, NULL);
};



int main(int argc, char** argv) {

    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server* server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    CNC_Eding ProLight1000;

    // Connect to the Eding server
    int rc = ProLight1000.Login();
    if (rc == -10 || rc == -15 || rc == 17) {

      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "OPCUA Server couldn't connect to EdingCNC Server");
      return 0;
    }
    else {
      // instanciaVectFunct_GCC_lido_II é uma cópia do instanciaVectFunct_GCC_lido
      VectFunctions_GenericCncClass instanciaVectFunct_GCC_lido_II = XmlParse();

      // create nodes from the NodeSet
      if (namespace_cnc_generated(server) != UA_STATUSCODE_GOOD) {

        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the CNC NodeSet");
      }
      else {
        namespace_cnctest_generated(server);

        StaticValues(server);

        /// Incluir os Métodos no Servidor ///
        UA_Server_setMethodNodeCallback(server, UA_NODEID_STRING(3, "a.s7005"), loadJobCallBack);
        UA_Server_setMethodNodeCallback(server, UA_NODEID_STRING(3, "a.s7006"), pauseJobCallBack);
        UA_Server_setMethodNodeCallback(server, UA_NODEID_STRING(3, "a.s7007"), resetCallBack);
        UA_Server_setMethodNodeCallback(server, UA_NODEID_STRING(3, "a.s7008"), rewindJobCallBack);
        UA_Server_setMethodNodeCallback(server, UA_NODEID_STRING(3, "a.s7009"), runResumeJobCallBack);

        // call the PeriodicUpdateValues Callback every 0.5 sec.
        UA_Server_addRepeatedCallback(server, periodicUpdateValues, &instanciaVectFunct_GCC_lido_II, 500, NULL);

        UA_StatusCode retval = UA_Server_run(server, &running);
        UA_Server_delete(server);
        return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
      };
    };
};
