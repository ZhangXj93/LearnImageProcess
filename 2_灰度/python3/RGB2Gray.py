import cv2
import numpy as np

def BGR2Gray(srcImage):

    b = srcImage[:,:,0]
    g = srcImage[:,:,1]
    r = srcImage[:,:,2]
    
    destImage = 0.2126 * r + 0.7152 * g + 0.0722 * b
    destImage = destImage.astype(np.uint8)

    return destImage

srcImage = cv2.imread("imori.jpg")
cv2.imshow("imori", srcImage)

destImage = BGR2Gray(srcImage)
cv2.imshow("destImage", destImage)

cv2.waitKey(0)
cv2.destroyAllWindows()