del = 25;

% Turbo encoder parameters
K = 3;  % Constraint length
R = 1/3;  % Code rate

% Generate the turbo encoder object
turboEnc = comm.TurboEncoder('TrellisStructure', poly2trellis(K, [6 7], 6), 'InterleaverIndicesSource', 'Input port');

% Initialize the Arduino board
a = arduino('COM4', 'Uno');
configureDigitalPin(a, 'D11', 'Output');
configureDigitalPin(a, 'D12', 'Output');

% Define the output functions
both = @() writeDigitalPin(a, 'D11', true); writeDigitalPin(a, 'D12', true);
one = @() writeDigitalPin(a, 'D11', true); writeDigitalPin(a, 'D12', false);
none = @() writeDigitalPin(a, 'D11', false); writeDigitalPin(a, 'D12', false);

% Send some initial signals
both();
pause(2);
one();
pause(2);
none();
pause(2);

% Continuously read input from the Arduino and transmit encoded bits
while true
    if a.NumBytesAvailable > 0
        input = read(a);
        fprintf('Input string: %s\n', input);
        
        % Convert the input string to a binary sequence
        binary = '';
        for i = 1:length(input)
            charBinary = dec2bin(input(i), 8);
            binary = [binary, charBinary];
        end
        fprintf('Binary sequence: %s\n', binary);
        
        % Encode the binary sequence using the turbo encoder
        encodedBits = turboEnc(logical(binary-'0'));
        fprintf('Encoded bits: %s\n', num2str(encodedBits'));
        
        % Transmit the encoded bits
        for i = 1:length(encodedBits)
            temp = num2str(encodedBits(i));
            if temp == '0'
                one();
                pause(del/1000);
            else
                both();
                pause(del/1000);
            end
        end
        none();
    end
end
