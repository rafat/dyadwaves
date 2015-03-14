## DeNoising ##

> If DyadWaves' denoising interface seems a bit intimidating, it is probably because it offers more choices than are necessary. Most available wavelets, decomposition level etc. won't give you acceptable results most of the time. A few wavelets (symmlets - sym4 and sym8, Daubechies orthogonal wavelets) are the ones you should probably work with. This software is aimed mostly at students and beginners in this field so it makes sense to have as many options as possible. I have used 2 methods ([visushrink](http://www-stat.stanford.edu/~donoho/reports.html#1993) and [sureshrink](http://www-stat.stanford.edu/~donoho/reports.html#1993)) for 1D and three methods([visushrink](http://www-stat.stanford.edu/~donoho/reports.html#1993), [sureshrink](http://www-stat.stanford.edu/~donoho/reports.html#1993) and [bayesshrink](http://infoscience.epfl.ch/record/33854)) for 2D .<sup>1,2,3</sup>

### 1D::Denoising ###

![https://lh4.googleusercontent.com/-RVlcs1Va7Cg/TiKZMrBvYRI/AAAAAAAAAIg/vtDpr9I91Qo/s800/denoisehs.png](https://lh4.googleusercontent.com/-RVlcs1Va7Cg/TiKZMrBvYRI/AAAAAAAAAIg/vtDpr9I91Qo/s800/denoisehs.png)
_Example:: 1D sureshrink Denoising of Wavelab Heavisine signal( SNR 8dB) using sym8 wavelet with SWT 4-level Decomposition_


### 2D::Denoising ###

![https://lh5.googleusercontent.com/-hEASwaI7t5Y/TiKenbCxyoI/AAAAAAAAAIw/ZVLfzBP4m-A/s800/denoiselena.png](https://lh5.googleusercontent.com/-hEASwaI7t5Y/TiKenbCxyoI/AAAAAAAAAIw/ZVLfzBP4m-A/s800/denoiselena.png)
_Example:: 2D bayesshrink Denoising of Lena 256X256 Image( SNR ~ 20 dB) using sym4 wavelet with dwtper 2 Level Decomposition_

![https://lh3.googleusercontent.com/-lI4nYGX4lKI/TiKgJJxAUnI/AAAAAAAAAI8/587T2aOp5S4/s800/denoisehouse.png](https://lh3.googleusercontent.com/-lI4nYGX4lKI/TiKgJJxAUnI/AAAAAAAAAI8/587T2aOp5S4/s800/denoisehouse.png)
_Example:: 2D bayesshrink Denoising of House 256X256 Image( SNR ~ 20 dB) using sym4 wavelet with dwtsym 3 Level Decomposition_

**DeNoising References**

1.  David L. Donoho, Iain M. Johnstone, Gerard Kerkyacharian, Dominique Picard. Wavelet Shrinkage: Asymptopia. _Journal of the Royal Statistical Society. Series B (Methodological), Vol. 57, No. 2. (1995), pp. 301-369_ [Link](http://www-stat.stanford.edu/~donoho/reports.html#1993)

2. Iain M.Johnstone David L Donoho. Adapting to smoothness via wavelet shrinkage. _Journal of the Statistical Association, 90(432):1200–1224, Dec 1995._ [Link](http://www-stat.stanford.edu/~donoho/reports.html#1993)

3.  Martin Vetterli, S Grace Chang, Bin Yu. Adaptive wavelet thresholding for image denoising and compression. _IEEE Transactions on Image Processing, 9(9):1532–1546, Sep 2000._ [Link](http://infoscience.epfl.ch/record/33854)