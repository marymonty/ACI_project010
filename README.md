# ACI_project010
the camera project for art &amp;&amp; code &amp;&amp; interactivity

much of the idea for the code came from opencv example code - both gotten from the example in the openFrameworks directory we looked at in class, and from another example on the OF github that shows how to use the opencv import. 

This program has the user interact with the webcam by using their body to make choices on the screen of what they want to do to play a midi sort of keyboard. 

Initially the webcam learns what is in the screen as the background, to reset the background you can press spacebar. 
Anything new introduced into the screen should be recorded as a contour, and should be boxed in with contour lines. 
When the user moves the contour box over the text options (by pointing to the options or what have you) there should be new options introduced on the screen for the user to interact with (point to). At the piano or voiceover screens there will also be choices to get back to the main text screen in the bottom corners. If you learn the background and you introducing something new to the screen does not find a contour box, you can try to change the threshold with the '-' and '+' buttons. 
