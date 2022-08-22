import cv2
import numpy as np

def AveragePooling(srcImage, G = 8):

    destImage = srcImage.copy()
    
    H, W, C = destImage.shape
    nH = int(H / G)
    nW = int(W / G)
    
    for y in range(nH):
        for x in range(nW):
            for c in range(C):
                destImage[y*G:(y+1)*G, x*G:(x+1)*G, c] = np.max(destImage[y*G:(y+1)*G, x*G:(x+1)*G, c]).astype(np.int)

    return destImage


srcImage = cv2.imread("imori.jpg")
cv2.imshow("imori", srcImage)

destImage = AveragePooling(srcImage)
cv2.imshow("destImage", destImage)


cv2.waitKey(0)
cv2.destroyAllWindows()