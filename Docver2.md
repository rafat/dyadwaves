<div>

<h1>DyadWaves version 0.2.0.1</h1>

<h2>Documentation</h2>

<h1>1 Overview</h1>

<div>DyadWaves is an easy to use GUI for 1D and 2D Wavelet Transform. This software is pretty basic with functionality consisting of Wavelet Transform computation, signal/image approximation and denoising using up to three transform modes. It uses separate executables for 1D and 2D processing that are appropriately labeled. This software is build using C++ and Nokia’s QT4(<a href='http://qt.nokia.com/'>http://qt.nokia.com/</a>). 1D Dyadwaves graphs are build using QWT library courtesy of Qwt project (<a href='http://qwt.sf.net'>http://qwt.sf.net</a>). FFT computations are done using FFTW3 library (<a href='http://www.fftw.org'>http://www.fftw.org/</a>). </div>

<h2>1.1 Transform Modes</h2>

<div> There are three available modes. </div>

1. dwt_sym - Decimated Discrete Wavelet Transform using symmetric extension.<br>
<br>
2. dwt_per - Decimated Discrete Wavelet Transform using periodic extension.<br>
<br>
3. Stationary (Undecimated) Wavelet Transform. It also uses peiodic extension.<br>
<br>
<h2>1.2 Wavelet Families</h2>

<div> Four wavelet families are currently available. </div>

1. Daubechies- 15 orthogonal wavelets are available, ranging from 2-tap filters to 30-tap filters.<br>
<br>
2. Biorthogonal - Symmetric filter non-orthogonal wavelets. bior1.1 to bior6.8<br>
<br>
3. Coiflets - 5 wavelets. coif1 - coif5.<br>
<br>
4. Symmlets - 10 wavelets from sym1 to sym10.<br>
<br>
<div> Wavelets, associated filters and filter frequency response can be plotted by selecting the wavelet from the "Choose Wavelet Family" dropdown box in the DWT Dashboard and then using appropriate pushbuttons in the Display Dashboard as shown below. </div>

<h2>1.3 Input/Output</h2>

<div><div><img src='https://lh3.googleusercontent.com/-fnDTnYKMDU8/TkWmFYYcIjI/AAAAAAAAAJU/PuxMQLfIEuQ/s800/wavedisp.png' /></div></div>

<div> <b>1D</b> :: 1D I/O is very, very basic at this point. It accepts text/data files arranged in either one row or one column.To view the data format you may want to check the dyadwaves folder after running dyadwaves. Default signal is saved as defaultsignal.txt. You can save outputs (coefficients and processed signal) in the same 1D text/data format or you can save graphs as image/pdf/svg files. </div>

<div> <b>2D</b> :: Input is in the form of images ( tif,tiff,jpeg,bmp,png). Output images can be saved in these same five formats. Two more formats are added - xbm and xpm for X11 systems. </div>

<h2>1.4 1D Interface</h2>

<div> 1D Interface displays input and output graphs. These graphs can be zoomed in and zoomed out. IDWT graphs have additional options of saving and viewing each graph separately as the display view can get very busy if decomposition levels are large specially if screen resolution isn’t very high. </div>

<div><div><img src='https://lh5.googleusercontent.com/-icBj6Pgn5NI/TkWmj68YufI/AAAAAAAAAJw/xctsSWJ3X1Q/s912/disp1d-1.png' /></div></div>

<div> Graphs can also be viewed and saved in printer-friendly format(blue on white). </div>
<div><div><img src='https://lh4.googleusercontent.com/-c16Vn26tjVE/TkWmkpD4cPI/AAAAAAAAAJ0/EIkvJHfevwU/s912/disp1d-2.png' /></div></div>

<div> Please also note that "save as PDF/SVG" format will also save outputs in the five image format and uses rendering of the graph which in most cases result in better quality ouputs. "Save as Image" is the quick and dirty format and will capture the pixmap as is so the results may not be up to par on many occasions. </div>

<h2>1.5 2D Interface</h2>

<div> 2D interface display is similar to the 1D case minus any zoom functionality. However, if the images are large they may not fit in the application window or they may not appear proportionally to their dimensions. In such a case, you have the option of viewing full size image. There is also an option of viewing all DWT coefficients. These are liberally zeropadded in order to have a rectangular image. </div>

<div><div><img src='https://lh5.googleusercontent.com/-U8m8GI93xpw/TkWmzhYRgcI/AAAAAAAAAKA/lIuAusQhcjw/s912/disp2d-1.png' /></div></div>

<div> Full size Decomposition can be viewed using “View FullSize Image” button. “Expansive View” is available for grayscale images and it consists of displaying all coefficients with extensive zeropadding to keep the dimensions rectangular. </div>

<div><div><img src='https://lh3.googleusercontent.com/-sN-HfS3ptJY/TkWm1EORU4I/AAAAAAAAAKE/_Yn8xD9rEtM/s912/disp2d-2.png' /></div></div>

<h2>1.6 Changes from Previous (0.1.2.2) Version</h2>

<div> A couple of major and several minor changes: </div>

<div> 1. The Interface is slightly different. There are no Menu or Tool Bars. Menu can be accessed from the "INPUT MENU" button. This is done for aesthetics, performance and implementational reasons. </div>

<div> 2. Denoising Bug that caused Image Denoising to crash for 1-scale color Denoising has been fixed. </div>

<div> 3. Another Major fix involves getting rid of artifacts that were caused in approximated and denoised images because of QT4 using modulus of overflow RGB values instead of scaling them down. </div>

<div> 4. 1D DyadWaves now accepts <b>.dat files as well as</b>.txt files. It will also save coefficients in these two formats. The output is still restricteded to being 1D row/column vector. I expect to add more options in future releases. </div>

<div> 5. 2D DyadWaves2D loads/saves more image formats including X11 bitmap/pixmap formats. </div>

<div> 6. Image FFT can now be saved in all available image formats. </div>

<h1>2 Wavelet Transform</h1>

<div> There are three wavelet transform modes - dwt_sym, swt and dwt_per. All of them have same display system and the DWT output can be saved as text file using the "Save DWT Output" button in the 1D mode and as image in 2D mode. </div>

<h2>2.1 1D Decimated DWT (Symmetric Extension)</h2>

<div> Of all the modes , this one is the best equipped to deal with signal boundary issues and gives excellent results for symmetric and nearly symmetric wavelets. Signal is symmetrically extended at every stage so there are no sharp jumps and discontinuities. On the negative side, there is some redundancy in the system as this isn’t an N input N output system. </div>

<div><div><img src='https://lh4.googleusercontent.com/-1RNrzXrXE-Q/TkWmNZNtQYI/AAAAAAAAAJg/vMoztQgL4M4/s800/db1.png' /></div></div>

<h2>2.2 1D Stationary Wavelet Transform (Undecimated)</h2>

<div> For 1D case, an N input signal yields 2XN output coefficients at each stage. There is more redundancy but it is useful in cases where translation-invariance is needed. This software also uses SWT (alongside the other two modes) for denoising. </div>

<div><div><img src='https://lh6.googleusercontent.com/-jVroXdGz0y8/TkWm_UqTD6I/AAAAAAAAAKQ/bzQ40Z9y-3A/s912/swt.png' /></div></div>

<h2>2.3 1D Decimated DWT (Periodic Extension)</h2>

<div> dwt_per mode is a N input and ~N output system and ,thus, often is the fastest scheme of the three.Although, periodic extension may sometimes result in subpar performance at the signal boundaries. Regardless, having least redundancy makes it suitable for some approximation applications. </div>

<div><div><img src='https://lh3.googleusercontent.com/-TSltt_Fd7P0/TkWm3SDES4I/AAAAAAAAAKI/DSY1upFJaEg/s800/dwt_per.png' /></div></div>

<h2>2.4 2D Decimated DWT (Symmetric Extension)</h2>

<div> 2D DWT is similar to 1D in terms of options with one exception - you have an option of faster processing a color image by treating it as a grayscale image. This is due to speed issues in this implementation. Smaller Images ( < 512 X 512) shouldn’t be too much of a nuisance on most systems. </div>

<div><div><img src='https://lh6.googleusercontent.com/-wZfMH8_PVx0/TkWnQegHonI/AAAAAAAAAKY/st4sVnflZWo/s912/sym2d.png' /></div></div>

<h2>2.5 2D Stationary Wavelet Transform (Undecimated)</h2>

<div> Same goes for Stationary Wavelet Transform with the additional caution that speed is an even bigger of an issue for high number of decomposition levels( > 2 actually if color image is large in size). </div>

<div><div><img src='https://lh3.googleusercontent.com/-LUtBGpDdr_I/TkWmbE61hrI/AAAAAAAAAJs/KrYEsn2MZvo/s912/db1-2.png' /></div></div>

<h2>2.6 2D Decimated DWT (Periodic Extension)</h2>

<div><div><img src='https://lh6.googleusercontent.com/-xo5IklMYG7A/TkWmyrBWiXI/AAAAAAAAAJ8/3NCJ2NNmU5I/s912/dwt2dper2.png' /></div></div>

<h1>3 Approximation</h1>

<div> DyadWaves uses a very simple approximation algorithm. User can select the wavelet name from the DWT Dashboard, percent of non-zero coefficients and the wavelet mode(Either dwt_per or dwt_sym) from the Approximation Dropdown menu. Based on the percentage selected, the algorithm calculates the hard universal threshold and zeroes all coefficients that have values below that threshold. Inverse DWT is then computed to reconstruct the signal from the non-zero coefficients. dwt_per has fewer coefficients so it gives better results in most cases. </div>

<div><div><img src='https://lh5.googleusercontent.com/-GIRxtOCrg8g/TkWmFqa5w4I/AAAAAAAAAJY/uh3N-H5NZBk/s800/appx1d.png' /></div></div>

<div><div><img src='https://lh4.googleusercontent.com/-Ec7WYwRGUHw/TkWmLgM4rFI/AAAAAAAAAJc/K1CokGZa7FY/s912/appx2d.png' /></div></div>

<div> Note-No compression algorithms are implemented. This is just a demonstration of wavelet approximation properties. However, you can access 1D approximation coefficients which may be helpful in implementation of compression algorithms. </div>

<h1>4 Denoising</h1>

<div> If DyadWaves’ denoising interface seems a bit intimidating, it is probably because it offers more choices than are necessary. Most available wavelets, decomposition level etc. won’t give you acceptable results most of the time. A few wavelets (symmlets - sym4 and sym8, Daubechies orthogonal wavelets) are the ones you should probably work with. This software is aimed mostly at students and beginners in this field so it makes sense to have as many options as possible. I have used 2 methods (visushrink and sureshrink) for 1D and three methods(visushrink, sureshrink and bayesshrink) for 2D. </div>

<h2>4.1 1D Denoising</h2>

<div> Example below shows 1D sureshrink Denoising of Wavelab Heavisine signal( SNR 8dB) using sym8 wavelet with SWT 4-level Decomposition </div>

<div><div><img src='https://lh3.googleusercontent.com/-zdbvrf4DGdQ/TkWmT2VOupI/AAAAAAAAAJk/1Ddl7Q5mfCk/s912/denoisehs.png' /></div></div>

<h2>4.2 2D Denoising</h2>

<div> The two examples show 2D bayesshrink Denoising of Lena 256X256 Image( SNR ~ 20 dB) using sym4 wavelet with dwt_per 2 Level Decomposition and </div><div> 2D bayesshrink Denoising of House 256X256 Image( SNR ~ 20 dB) using sym4 wavelet with dwt_sym 3 Level Decomposition. </div>

<div><div><img src='https://lh4.googleusercontent.com/-BNj3DjZGiig/TkWml1h737I/AAAAAAAAAJ4/hda16_lkjkc/s800/denoiselena.png' /></div></div>

<div><div><img src='https://lh3.googleusercontent.com/-eTNf8RUzRdY/TkWmaapEZ2I/AAAAAAAAAJo/Nhro5QAMbjc/s912/denoisehouse.png' /></div></div>

<h1>5 Issues, FAQs and Contact</h1>

<div> DyadWaves version 0.2.0.1 </div><div> Documentation: <a href='http://code.google.com/p/dyadwaves/wiki/Overview'>http://code.google.com/p/dyadwaves/wiki/Overview</a> and <a href='http://dyadwaves.sourceforge.net'>http://dyadwaves.sourceforge.net</a> </div><div> License : GNU GPL </div><div> Source Code: See src folder of the download. Latest code will be available at <a href='http://code.google.com/p/dyadwaves/source/browse/#svn'>http://code.google.com/p/dyadwaves/source/browse/#svn</a> </div><div>'''Notes on Linux Installation''' : This version also contains a Linux tarball (dyadwaves.tar.gz). All the images shown above are screenshots of dyadwaves running in Ubuntu 10.04LTS. I have also tested the tarball on Ubuntu 7.10. Please read the README file in dyadwaves.tar.gz. </div><div> This Wavelet GUI for windows/unix systems is practically in alpha testing stage and it has some stability issues. There is also the matter of its speed not being upto the par and this will require some code rewrite from the scratch. In the meantime you may want to work in the grayscale mode for images larger than 512 X 512. I’ve added "View DWT Report" button which will return the DWT computation time so you can plan accordingly. "View DWT Report" will NOT return accurate number of coefficients in 1D dwt_sym case. If you come across any errors or you have any suggestions, complaints and/or advice I can be reached at </div><div> rafat.hsn -at- gmail.com </div>
<hr />

Copyright (C) Rafat Hussain, 2011 Documentation<br>
<br>
</div>