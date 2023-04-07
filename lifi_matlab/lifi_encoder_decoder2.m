%reading a image
clc, clear, close all

im = imread("0x0.bmp");

%displaying image

figure('Name','Original','NumberTitle','off');
imshow(im);
title('Original');

%red green blue matrix of image separate for transmission

red = im(:, :, 1);

green = im(:, :, 2);

blue = im(:, :, 3);

%converting each matrix into a byte stream

bin_seq_red = reshape(de2bi(red(:), 8, 'left-msb').', [], 1);

bin_seq_green = reshape(de2bi(green(:), 8, 'left-msb').', [], 1);

bin_seq_blue = reshape(de2bi(blue(:), 8, 'left-msb').', [], 1);

% Set up turbo encoder object
turbob_encoder = comm.TurboEncoder('InterleaverIndices', 1:numel(bin_seq_red));

% Turbo encode binary sequence
encoded_red = turbob_encoder(bin_seq_red(:));
encoded_green = turbob_encoder(bin_seq_green(:));
encoded_blue = turbob_encoder(bin_seq_blue(:));

%Turbo decode a binary sequence

% Set up the turbo decoder object
tbcd = comm.TurboDecoder('InterleaverIndices', 1:numel(encoded_red));

% Turbo decode the encoded binary sequence
decoded_bits = tbcd(encoded_red);


