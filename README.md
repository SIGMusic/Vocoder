
# Vocoder Plugin

## File Structure:
```
Vocoder/                # Project folder
│   ├── source/             # Source code
│   ├── libs/               # JUCE submodule
│   ├── VST3 Builds/        # Empty folder for VST3 binaries
│   └── Vocoder.jucer       # Projucer project file
```

## Overview:
This repository includes the Vocoder plugin project along with JUCE as a submodule under the **`libs/JUCE`** directory. **VST3 Builds** is an empty directory used as the default location where **VST3** binary files will be copied post-build.

Please do not edit the **`Vocoder.jucer`** in Projucer without proper communication. We want to keep the configurations consistent across all platforms, and edits to this file might cause conflicts in setup or export for other contributors.

## Windows Setup:

### Step 1: Clone the Repository and Initialize Submodules
When you clone the repo, make sure you initialize the submodules:
```bash
git clone --recurse-submodules https://github.com/SIGMusic/Vocoder.git
```

### Step 2: Build JUCE Tools
1. **Open Visual Studio 2022**.
2. Navigate to `libs/JUCE/extras/Projucer/Builds/VisualStudio2022` and build the `Projucer.sln` solution file.
3. Navigate to `libs/JUCE/extras/AudioPluginHost/Builds/VisualStudio2022` and build the `AudioPluginHost.sln` solution file.

### Step 3: Configure Global Paths in Projucer
1. **Open the `Vocoder.jucer` file** in **Projucer**.
2. In **File → Global Paths**:
	* Set **JUCE Modules** to:  
   			`<YourProjectRootDirPath>\libs\JUCE\modules`
   
	* Set **Path to JUCE** to the location of the **JUCE submodule**:  
  	 		`<YourProjectRootDirPath>\libs\JUCE`

### Step 4: Set Debug Command in Visual Studio
In **Visual Studio**:
1. **Debug** → **Debug Properties**.
2. Navigate to **Configuration Properties** → **Debugging**.
3. Set the **Command** field to:
   ```sh
   <YourProjectRootDirPath>\libs\JUCE\extras\AudioPluginHost\Builds\VisualStudio2022\x64\Debug\App\AudioPluginHost.exe
   ```

### Step 5: Configure AudioPluginHost for VST3 Plugin Search
In **AudioPluginHost**:
1. Add a new **VST3 Plugin Search Directory**, set to the **VST3 Builds** folder.
   ```sh
	 <YourProjectRootDirPath>\VST3 Builds\
	 ```

---

## macOS Setup:  
*To be added*  

---

## Notes:
- Please let us know if you encounter any issues or need help with setup!
- When you build your plugin in Visual Studio, it will copy the **VST3** binary into the **VST3 Builds** folder, making it easier to find and use for testing with **AudioPluginHost** than the default dump location.
- Be sure to work in a separate branch for each feature and `git pull` every time before working!


