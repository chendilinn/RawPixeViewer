# RawPixeViewer

A powerful and lightweight desktop tool for viewing raw pixel data from binary files. Designed for developers, engineers, and researchers working with uncompressed image sensors, video codecs, and computer vision algorithms.

This application allows you to open any binary file and interpret its contents as video frames, with full control over resolution, pixel format, and memory layout.

## Features

- **Wide Format Support**: Natively decodes and displays पोहोच popular YUV and RGB formats.
- **Large File Handling**: Uses memory mapping (`QFile::map`) to instantly open and process multi-gigabyte files without consuming significant RAM.
- **Interactive Playback**: 
    - Play/Pause functionality.
    - Adjustable frame rate (FPS).
- **Precise Frame Navigation**:
    - Step forward/backward frame by frame.
    - Directly jump to any specific frame number.
- **Configurable Parameters**: Easily set and modify:
    - Image Width & Height
    - Pixel Format
    - Linesize (Stride) for handling memory padding.
- **Responsive UI**: A clean and straightforward interface built with Qt 6.

## Supported Pixel Formats

- **YUV 4:2:0 Planar**: `YUV420P (I420/YU12)`
- **YUV 4:2:0 Planar (V/U swapped)**: `YUV420P (YV12)`
- **YUV 4:2:0 Semi-Planar**: `YUV420SP (NV12)`
- **YUV 4:2:0 Semi-Planar (V/U swapped)**: `YUV420SP (NV21)`
- **YUV 4:2:2 Planar**: `YUV422P (I422)`
- **RGB 24-bit**: `RGB888`
- **RGBA 32-bit**: `RGBA8888`

## How to Use

1.  **Open File**: Launch the application and go to `File -> Open...` to select your raw data file (e.g., `.yuv`, `.rgb`, or any other extension).
2.  **Configure Settings**: Use the **Settings** panel on the right to enter the correct parameters for your file:
    *   **Resolution**: Set the image width and height.
    *   **Pixel Format**: Select the corresponding format from the dropdown list.
    *   **Linesize**: Specify the number of bytes per row in memory. For tightly packed formats, this is typically `width * bytes_per_pixel`.
3.  **Navigate**: 
    *   Use the **Previous/Next Frame** buttons for stepping through frames.
    *   Enter a frame number and click **Jump** to go directly to that frame.
    *   Set the desired **FPS** and click **Play** to start video playback. The button will change to **Pause** to allow stopping the playback.

## Building from Source

### Prerequisites

- **Qt Framework**: Version 6.2 or newer.
- **CMake**: Version 3.16 or newer.
- A C++ compiler that supports C++17 (e.g., GCC, Clang, MSVC).

### Build Steps

1.  **Clone the repository:**
    ```bash
    git clone <your-repository-url>
    cd RawPixeViewer
    ```

2.  **Configure with CMake:**
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3.  **Compile the project:**
    ```bash
    cmake --build .
    ```

4.  The executable `RawPixeViewer` will be available in the `build` directory.

Alternatively, you can open the `CMakeLists.txt` file directly in a compatible IDE like **Qt Creator** and build the project from there.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
