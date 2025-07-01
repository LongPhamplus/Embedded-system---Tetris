# STM32F429I_DISCO_REV_D01 TBS

The default IDE is set to STM32CubeIDE, to change IDE open the STM32F429I_DISCO_REV_D01.ioc with STM32CubeMX and select from the supported IDEs (EWARM from version 8.50.9, MDK-ARM, and STM32CubeIDE). Supports flashing of the STM32F429I_DISCO_DEV_D01 board directly from TouchGFX Designer using GCC and STM32CubeProgrammer. Flashing the board requires STM32CubeProgrammer which can be downloaded from the ST webpage. 

This TBS is configured for 320 x 240 pixels 16bpp screen resolution.  

Performance testing can be done using the GPIO pins designated with the following signals: VSYNC_FREQ  - Pin PE2, RENDER_TIME - Pin PE3, FRAME_RATE  - Pin PE4, MCU_ACTIVE  - Pin PE5
 
## How to run

1. Create a folder name `TouchGFXProjects` in `C:` drive. 

2. Then open **Command Prompt**, then navigate to the folder by running

```bash
    cd C:\TouchGFXProjects 
```

3. Clone the repository: 

```
    git clone https://github.com/LongPhamplus/Embedded-system---Tetris.git
```

4. After that, go to STM32CubeIDE and open .project file. Connect to STM32 via USB.

5. Click **run**  button in STM32CubeIDE to build and run the project.

6. The Tetris game will run on your STM32 device. Enjoy !
   
***Note that the board configuration can be found in setup.txt"

