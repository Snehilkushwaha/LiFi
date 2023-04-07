% Read in image file
im = imread('0x0.png');

% Convert image to binary sequence
im_bw = im2bw(im);

% Set up turbo encoder object
tbc = comm.TurboEncoder('InterleaverIndices', 1:numel(im_bw));

% Turbo encode binary sequence
encoded = tbc(im_bw(:));

% display original and encoded images

subplot(1,2,1);
imshow(im);
title('Original Image');

subplot(1,2,2);
imshow(reshape(encoded, size(im_bw)));
title('Turbo Encoded Image');

%%
% Read in image file
clc, clear
im = imread('0x0.png');
figure(1);
imshow(im);
% Convert image to binary sequence
im_bw = im2bw(im);
%plot(im);
figure(2);
imshow(im_bw);

% Set up turbo encoder object
tbc = comm.TurboEncoder('InterleaverIndices', 1:numel(im_bw));

% Turbo encode binary sequence
encoded = tbc(im_bw(:));
sz = size(im_bw);
% Reshape the encoded sequence back into an image
encoded_im = reshape(encoded, sz);

% Display the encoded image
imshow(encoded_im);
title('Turbo Encoded Image');




%%

%breking image into rgb matrix and then combining it to form the image back

clc, clear, close all
im = imread("0x0.bmp");
im2 = imread("abstract-photography-design-feature.jpg");
figure('Name','Original','NumberTitle','off');
imshow(im);
title('Original');
red = im(:, :, 1);

green = im(:, :, 2);

blue = im(:, :, 3);



new = cat(3, red, green, blue);

figure('Name','Reconstructed','NumberTitle','off');
imshow(new);
title('Reconstructed');