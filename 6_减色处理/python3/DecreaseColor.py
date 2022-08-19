from email.mime import image
import cv2
import numpy as np

def DecreaseColor(srcImage):

    destImage = srcImage.copy()
    
    ind = np.where(destImage < 64)
    destImage[ind] = 32
    
    ind = np.where((destImage >= 64) & (destImage < 128))
    destImage[ind] = 96
    ind = np.where((destImage >= 128) & (destImage < 192))
    destImage[ind] = 160
    ind = np.where((destImage >= 192) & (destImage < 256))
    destImage[ind] = 224

    return destImage


srcImage = cv2.imread("imori.jpg")
cv2.imshow("imori", srcImage)

destImage = DecreaseColor(srcImage)
cv2.imshow("destImage", destImage)


cv2.waitKey(0)
cv2.destroyAllWindows()