%% --- File list and corresponding test frequencies ---
% Frequencies in Hz
freqs = [0.5:0.5:5, 8, 12, 16, 20];

% Build filenames
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
    
    % Extract time and signals (assuming same structure as before)
    t  = data.ScopeData_v1.time(:);        % time vector
    v1 = data.ScopeData_v1.signals.values(:);
    v2 = data.ScopeData_v2.signals.values(:);
    
    w = 2*pi*freqs(k);  % convert Hz to rad/sec
    
    % Fit sine waves
    [A1, P1] = fit_sine_wave(t, v1, w);
    [A2, P2] = fit_sine_wave(t, v2, w);
    
    % Store results
    gain_v1(k)  = A1;
    phase_v1(k) = P1;
    gain_v2(k)  = A2;
    phase_v2(k) = P2;
end

%% --- Output table ---
T = table(freqs(:), gain_v1, phase_v1, gain_v2, phase_v2, ...
          'VariableNames', {'Frequency_Hz','Gain_v1','Phase_v1','Gain_v2','Phase_v2'});

disp(T);
