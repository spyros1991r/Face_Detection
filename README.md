# Face_Detection

This is a program made in c++ language about the detection of faces in jpeg images. It is based on the algorithm which can be found here. http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=611173&url=http%3A%2F%2Fieeexplore.ieee.org%2Fiel4%2F76%2F13348%2F00611173 <br/>
The stages of the algorithm are: <br/>
1) Training: Provide the algorithm with parts of the human face so it can be trained according to their colour<br/>
2)Jpeg images are then given in order for the facial parts to be recognized ONLY depending on their colour <br/>
3) On the second stage a "window" is passed over the parts that are recognized as potential faces on the first stage. In this implementation there is only one size of window, though more can easily be added with just a few lines of code.<br/>
4)On the last stage potential face regions are tested with according to their dct values. If they do not follow the reuqired patterns they are eliminated. The values depend on the images so feel free to change them.<br/>
Lastly, since i did not have a  big dataset of face and non face images, the program is trained on the face of the video found among the files, though you can easily change that by re-training the algorithm with as many faces as you wish. All this can be found in Make_prop.cpp file.<br/>
<br/>
Feel free to ask any questions or metnion anything concerning the above.
