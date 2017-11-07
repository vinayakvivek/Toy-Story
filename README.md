# Toy story character rendering

## Compiling
```bash
    cd <project_dir>
	mkdir build
	cd build
	cmake ..
	make
```
- if build succeeds, an executable `toys` will be created in `build/`

## Key bindings
- `J`, `K` and `L`: toggle light1, light2 and spotlight respectively.
- `B`: selects Buzz model (selected by default)
- `H`: selects Hamm model
- If you have selected **Buzz**, parts of Buzz can be selected by the following: [key - part]
    - `0` - Hip
    - `1` - Torso
    - `2` - Neck
    - `3` - Left Upper Arm
    - `4` - Left Lower Arm
    - `5` - Left Hand
    - `6` - Right Upper Arm
    - `7` - Right Lower Arm
    - `8` - Right Hand
    - `SHIFT + 0` - Left Thigh
    - `SHIFT + 1` - Left Leg
    - `SHIFT + 2` - Right Thigh
    - `SHIFT + 3` - Right Leg
    - `SHIFT + 4` - Left Foot
    - `SHIFT + 5` - Right Foot
- If you have selected **Hamm**, parts of Buzz can be selected by the following: [key - part]
    - `0` - Torso
    - `1` - Head
    - `3` - Front Left Leg
    - `4` - Front Right Leg
    - `5` - Back Left Leg
    - `6` - Back Right Leg
- After selecting, parts can be rotated. (each part have rotational restrictions!)
    - `W`, `S` - along Y-axis
    - `A`, `D` - along X-axis
    - `Q`, `E` - along Z-axis
- If you have selected `0`th node in a model (select model, press `0`), then the model can be translated by pressing `SHIFT` + [`A`, `D`, `Q`, `E`]
- Camera can be rotated using `ARROW` keys, `PAGE UP` and `PAGE DOWN`.
- Camera can be translated using `SHIFT` + [`ARROW` keys, `PAGE UP`, `PAGE DOWN`].
- Use `Z` and `X` to zoom in and out camera respectively.
