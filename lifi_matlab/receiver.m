
del = 25;

s = serialport("COM3", 9600); % Replace "COM3" with the appropriate port name
configureTerminator(s, "LF");
flush(s);

write(s, "A0" + newline); % Set the pin mode to INPUT on pin A0
pause(1);
one = str2double(readline(s));
pause(2);
zero = str2double(readline(s));
pause(2);
ambient = str2double(readline(s));
pause(1);

disp(ambient);
disp(zero);
disp(one);

% Set up the turbo decoder
turboDecoder = comm.TurboDecoder('TrellisStructure', poly2trellis(4, [13 15], 13), 'InterleaverIndices', 1:384);

while true
    binary = "";
    while str2double(readline(s)) > (ambient+20)
        if str2double(readline(s)) > (one-20) && str2double(readline(s)) < (one+20) % one
            binary = binary + "1";
            pause(del/1000);
        elseif str2double(readline(s)) > (zero-20) % zero
            binary = binary + "0";
            pause(del/1000);
        end
    end

    % Decode the received binary sequence
    if length(binary) >= 384
        encodedBits = logical(double(binary(:))-'0');
        decodedBits = step(turboDecoder, encodedBits);
        output = "";
        for i = 1:8:length(decodedBits)
            charBinary = decodedBits(i:i+7);
            charOutput = char(bin2dec(charBinary));
            output = strcat(output, charOutput);
        end
        disp("Output string: " + output);
        disp(decodedBits');
    end
end
