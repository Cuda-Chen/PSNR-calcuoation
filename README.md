# PSNR Calculation
Calculating MSE and PSNR between two same image which are original and processed, respectively.

# How to Compile and Run
```shell=
$ make
$ ./PSNRCalculation
```
# Usage
Type the following command if you merely want to know the MSE and PSNR
```shell=
$ ./PSNRCalculation [*original image's filename*] [*processed iamge's filename*]
```
If you want to know a bunch of pictures' MSE and PSNR
1. Just type filename of the pictures and their modified results in ```file_list.txt```
, which locates in the root directory of this work.
2. Then execute this program in the following command:
```
$ ./PSNRCalculation
```
3. After execution, you will find a file called ```mse_psnr.csv``` in root directory
, which is the MSE and PSNR of the pictures you type in step 1.

