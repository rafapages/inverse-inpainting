# Background removal by inverse inpainting

This simple method uses Telea's inpainting algorithm to remove the background of an image by extending the foreground. It is necesary to provide the mask which determines the background.

The method takes three arguments:

1. Original input image
2. Original input mask
3. Name of the extended output image
