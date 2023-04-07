%reading a image
clc, clear, close all

im = imread("0x0.bmp");

%displaying image

figure('Name','Original','NumberTitle','off');
imshow(im);
title('Original');


%red green blue matrix of image separate for transmission

red = dec2bin(im(:, :, 1));

green = im(:, :, 2);

blue = im(:, :, 3);


% Set up turbo encoder object
turbob_encoder = comm.TurboEncoder('InterleaverIndices', 1:numel(red));

% Turbo encode binary sequence
encoded_red = turbob_encoder(red);