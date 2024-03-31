# VisionerFile

Visioner implementation based on reading images from `input` folder. Expects images of following types:

- `input/object_good_*` - image of an object for positive response
- `input/object_bad_*` - image of an object for negative response
- `input/scene_*` - image of a scene for recognition

In theory, reads all major image formats, but tested only with `jpg`.
