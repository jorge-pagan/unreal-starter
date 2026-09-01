// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class END2602EditorTarget : TargetRules
{
	public END2602EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("END2602");
        AddAutoCommitPostBuild();
    }

    void AddAutoCommitPostBuild()
    {
        // Adjust path to where your script lives
        string ScriptPath = Path.Combine(ProjectFile.Directory.FullName, "Source", "auto_commit.bat");
        ScriptPath = ScriptPath.Replace("/", "\\");

        PostBuildSteps.Add($"call \"{ScriptPath}\" \"{ProjectFile.Directory.FullName}\"");
    }
}
