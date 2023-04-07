clc, clearvars, close all

YourImage = imread('0x0.png', 'png');

bits = reshape((dec2bin(typecast(YourImage(:), 'uint8'), 8) - '0').', 1, []);

  
encode = comm.TurboEncoder();
%%
% for i = 1:size(bits/8)
%     test = bits(i, i+64)
test = bits(1:64);
encoded_msg = encode(test);

decode = comm.TurboDecoder;

% orig_class = class(YourImage);


% orig_size = size(YourImage);
% reconstructed = reshape(typecast(uint8(bin2dec(char(reshape(bits, 8, [])+'0').')), orig_class), orig_size);
% imshow(reconstructed); title('reconstructed')

%%

clc, clearvars, close all

YourImage = imread('0x0.png', 'png');

input_bits = reshape((dec2bin(typecast(YourImage(:), 'uint8'), 8) - '0').', 1, []);

% Define the input binary sequence
%input_bits = [1 0 1 1 0 0 0 1 0 1 1 1 0 1 0 0 1 0 1 1 0 0 1 0 1 1 1 0 0 0 1];

% Set up the turbo encoder object
tbce = comm.TurboEncoder('InterleaverIndices', 1:numel(input_bits));

% Turbo encode the binary sequence
encoded_bits = tbce(input_bits.');

% Display the input and output binary sequences

%disp(['Input bits: ' num2str(input_bits)]);
%disp(['Encoded bits: ' num2str(encoded_bits.')]);

% Define the encoded binary sequence
%encoded_bits = [1 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 1];

% Set up the turbo decoder object
tbcd = comm.TurboDecoder('InterleaverIndices', 1:numel(encoded_bits));

% Turbo decode the encoded binary sequence
decoded_bits = tbcd(encoded_bits.');

img_reconstructed = reshape(bi2de(reshape(decoded_bits, 8, []).', 'left-msb'), size(img));

% Display the decoded binary sequence
%disp(['Decoded bits: ' num2str(decoded_bits.')]);
figure;
subplot(1, 2, 1);
imshow(img);
title('Original Image');
subplot(1, 2, 2);
imshow(img_reconstructed);
title('Reconstructed Image');






%%
% %image to code then code to image

% Read in the image
img = imread('0x0.png');

% Convert the image to a binary sequence
bin_seq = reshape(de2bi(img(:), 8, 'left-msb').', [], 1);

% Convert the binary sequence back to the image
img_reconstructed = reshape(bi2de(reshape(bin_seq, 8, []).', 'left-msb'), size(img));

% Display the original and reconstructed images
figure;
subplot(1, 2, 1);
imshow(img);
title('Original Image');
subplot(1, 2, 2);
imshow(img_reconstructed);
title('Reconstructed Image');



