// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class QRGenerator : ModuleRules
{
	public QRGenerator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ModuleDirectory, "Public"),
				Path.Combine(ModuleDirectory, "Public/zxing")
			}
		);

		PrivateIncludePaths.AddRange(
			new string[]
			{
				Path.Combine(ModuleDirectory, "Private"),
				Path.Combine(ModuleDirectory, "Private/zxing")
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"RenderCore",
				"RHI"
			}
		);

		// Ensure runtime artifacts in this plugin's Binaries/Win64 are staged (DLL/ONNX)
		string pluginBinariesWin64 = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Binaries/Win64"));
		if (Directory.Exists(pluginBinariesWin64))
		{
			var stageExtensions = new System.Collections.Generic.HashSet<string>(new string[] { ".dll", ".onnx" }, System.StringComparer.OrdinalIgnoreCase);
			foreach (var filePath in Directory.GetFiles(pluginBinariesWin64))
			{
				string extension = Path.GetExtension(filePath);
				if (!string.IsNullOrEmpty(extension) && stageExtensions.Contains(extension))
				{
					string fileName = Path.GetFileName(filePath);
					RuntimeDependencies.Add($"$(PluginDir)/Binaries/Win64/{fileName}");
				}
			}
		}
	}
}