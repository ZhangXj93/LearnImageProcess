from email.mime import image
import cv2
import numpy as np

def BGR2HSV(srcImage):

    image = srcImage.copy() / 255. #[0,1]
    
    destImage = np.zeros_like(image, dtype=np.float32)
    
    max_v = np.max(image, axis=2)
    min_v = np.min(image, axis=2)
    min_arg = np.argmin(image, axis=2)
    
    # H
    destImage[..., 0][np.where(max_v == min_v)] = 0
    ## if min == B
    ind = np.where(min_arg == 0)
    destImage[..., 0][ind] = 60 * (image[..., 1][ind] - image[..., 2][ind]) / (max_v[ind] - min_v[ind]) + 60
    
    ## if min == R
    ind = np.where(min_arg == 2)
    destImage[..., 0][ind] = 60 * (image[..., 0][ind] - image[..., 1][ind]) / (max_v[ind] - min_v[ind]) + 180
    
    ## if min == G
    ind = np.where(min_arg == 1)
    destImage[..., 0][ind] = 60 * (image[..., 2][ind] - image[..., 0][ind]) / (max_v[ind] - min_v[ind]) + 300
    
    # S
    destImage[..., 1] = max_v - min_v
    
    # V
    destImage[..., 2] = max_v

    return destImage


srcImage = cv2.imread("imori.jpg")
cv2.imshow("imori", srcImage)

destImage = BGR2HSV(srcImage)
# Transpose Hue
destImage[..., 0] = (destImage[..., 0] + 180) % 360
cv2.imshow("destImage", destImage)


cv2.waitKey(0)
cv2.destroyAllWindows()