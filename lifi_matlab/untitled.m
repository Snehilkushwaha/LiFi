% Set the parameters
fs = 44100; % Sampling frequency in Hz
duration = 1; % Duration of the sound in seconds
frequency = 10000; % Frequency of the sound in Hz

% Generate the sound wave
A = 0.1;
t = 0:1/fs:duration-1/fs; % Time vector

sound_wave = 0.001*sin(2*pi*frequency*t);
sound(sound_wave, fs);
% for i = 1:10
%     sound_wave = A*sin(2*pi*frequency*t);
%     sound(sound_wave, fs);
%     A = A+0.1;
%     
% end

% Play the sound
%sound(sound_wave, fs);
