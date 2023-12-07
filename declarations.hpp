namespace SDK
{
    // ScriptStruct Core.Object.Rotator
    // 0x000C
    struct FRotator
    {
        int Pitch; // 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
        int Yaw;   // 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
        int Roll;  // 0x0008 (0x0004) [0x0000000000000001]              ( CPF_Edit )
    };

    // ScriptStruct Core.Object.Vector
    // 0x000C
    struct FVector
    {
        float X; // 0x0000 (0x0004) [0x0000000000000001]              ( CPF_Edit )
        float Y; // 0x0004 (0x0004) [0x0000000000000001]              ( CPF_Edit )
        float Z; // 0x0008 (0x0004) [0x0000000000000001]              ( CPF_Edit )
    };
}