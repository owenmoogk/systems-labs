%% --- File list and corresponding test frequencies ---
freqs = [0.5:0.5:5, 8, 12, 16, 20];

% Build filenames using underscore for decimal
files = cellfun(@(f) sprintf('2_6_%s.mat', strrep(num2str(f),'.','_')), ...
                num2cell(freqs), 'UniformOutput', false);

%% --- Initialize arrays to store results ---
gain_v1  = zeros(length(files),1);
phase_v1 = zeros(length(files),1);
gain_v2  = zeros(length(files),1);
phase_v2 = zeros(length(files),1);

%% --- Loop over files and fit sine waves ---
for k = 1:length(files)
    data = load(files{k});
    
    % Extract time and signals
    t  = data.ScopeData_v1.time(:);
    v1 = data.ScopeData_v1.signals.values(:);
    v2 = data.ScopeData_v2.signals.values(:);
    
    w = 2*pi*freqs(k);  % convert Hz to rad/sec
    
    % Fit sine waves
    [A1, P1] = fit_sine_wave(t, v1, w);
    [A2, P2] = fit_sine_wave(t, v2, w);
    
    % Compute gain relative to 2V input and phase in degrees
    gain_v1(k)  = A1 / 2;
    phase_v1(k) = rad2deg(P1);
    gain_v2(k)  = A2 / 2;
    phase_v2(k) = rad2deg(P2);
end

%% --- Output table ---
T = table(freqs(:), gain_v1, phase_v1, gain_v2, phase_v2, ...
          'VariableNames', {'Frequency_Hz','Gain_v1','Phase_v1_deg','Gain_v2','Phase_v2_deg'});

disp(T);

%% --- Bode plots ---
figure;

% Magnitude plot
subplot(2,1,1);
semilogx(freqs, 20*log10(gain_v1), 'b-o', 'LineWidth', 1.5); hold on;
semilogx(freqs, 20*log10(gain_v2), 'r-o', 'LineWidth', 1.5);
grid on;
ylabel('Magnitude (dB)');
title('Frequency Response (Bode Plot)');
legend('v1','v2');

% Phase plot
subplot(2,1,2);
semilogx(freqs, phase_v1, 'b-o', 'LineWidth', 1.5); hold on;
semilogx(freqs, phase_v2, 'r-o', 'LineWidth', 1.5);
grid on;
xlabel('Frequency (Hz)');
ylabel('Phase (deg)');
legend('v1','v2');
