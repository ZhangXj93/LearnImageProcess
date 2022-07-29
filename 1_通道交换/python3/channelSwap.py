import cv2

def BGR2RGB(srcImage):

    b = srcImage[:,:,0]
    g = srcImage[:,:,1]
    r = srcImage[:,:,2]
    
    destImage = srcImage.copy()
    destImage[:,:,0] = r
    destImage[:,:,1] = g
    destImage[:,:,2] = b

    return destImage

srcImage = cv2.imread("imori.jpg")
cv2.imshow("imori", srcImage)

destImage = BGR2RGB(srcImage)
cv2.imshow("destImage", destImage)

cv2.waitKey(0)
cv2.destroyAllWindows()