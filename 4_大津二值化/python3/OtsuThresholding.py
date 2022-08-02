import cv2
import numpy as np

def BGR2Gray(srcImage):

    b = srcImage[:,:,0]
    g = srcImage[:,:,1]
    r = srcImage[:,:,2]
    
    destImage = 0.2126 * r + 0.7152 * g + 0.0722 * b
    destImage = destImage.astype(np.uint8)

    return destImage

def OtsuThresholding(srcImage):
    max_sigma = 0
    max_t = 0
    
    for t in range(1, 255):
        v0 = srcImage[np.where(srcImage <= t)]
        if len(v0) > 0:
            m0 = np.mean(v0)
        else:
            m0 = 0
            
        w0 = len(v0) / (srcImage.shape[0] * srcImage.shape[1])
        
        v1 = srcImage[np.where(srcImage > t)]
        if (len(v1) > 0):
            m1 = np.mean(v1)
        else:
            m1 = 0
            
        w1 = len(v1) / (srcImage.shape[0] * srcImage.shape[1])
        
        sigma = w0 * w1 * ((m0 - m1)**2)
        if (sigma > max_sigma):
            max_sigma = sigma
            max_t = t
    
    print("threshold >>", max_t)
    return max_t
        
    

def Thresholding(srcImage, threshold = 128):
    srcImage[srcImage < threshold] = 0
    srcImage[srcImage > threshold] = 255
    return srcImage

srcImage = cv2.imread("imori.jpg")
cv2.imshow("imori", srcImage)

destImage = BGR2Gray(srcImage)
cv2.imshow("destImage", destImage)

max_t = OtsuThresholding(destImage)

destImage = Thresholding(destImage, max_t)
cv2.imshow("threshold image", destImage)

cv2.waitKey(0)
cv2.destroyAllWindows()