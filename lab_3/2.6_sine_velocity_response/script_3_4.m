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

%% --- Loop over files, fit sine waves, and plot ---
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
    
    % Store results
    gain_v1(k)  = A1 / 2;          % divide by input amplitude
phase_v1(k) = rad2deg(P1);     % convert to degrees
gain_v2(k)  = A2 / 2;          % divide by input amplitude
phase_v2(k) = rad2deg(P2);     % convert to degrees

    % Generate fitted sine waves
    v1_fit = A1 * sin(w*t + P1);
    v2_fit = A2 * sin(w*t + P2);
    
    % --- Plot ---
    figure;
    hold on;
    plot(t, v1, 'b', 'LineWidth', 1.2);        % original v1
    plot(t, v1_fit, 'b--', 'LineWidth', 1.5);  % fitted v1
    plot(t, v2, 'r', 'LineWidth', 1.2);        % original v2
    plot(t, v2_fit, 'r--', 'LineWidth', 1.5);  % fitted v2
    hold off;
    
    xlabel('Time (s)');
    ylabel('Output');
    title(sprintf('Frequency %.1f Hz: Original vs Fitted Sine Waves', freqs(k)));
    legend('v1 original','v1 fit','v2 original','v2 fit');
    grid on;
end

%% --- Output table ---
T = table(freqs(:), gain_v1, phase_v1, gain_v2, phase_v2, ...
          'VariableNames', {'Frequency_Hz','Gain_v1','Phase_v1_deg','Gain_v2','Phase_v2_deg'});

disp(T);
