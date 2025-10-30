% Parameters
A = 2;            % Input amplitude
fs = 1000;        % Sampling frequency (Hz) -- adjust if needed

% Find all relevant .mat files
files = dir('4_3A_*.mat');

% Parse frequencies from filenames
freqs = zeros(length(files),1);
for k = 1:length(files)
    name = erase(files(k).name, {'.mat', '4_3A_'});
    name = strrep(name, '_', '.');  % replace underscores with dots
    freqs(k) = str2double(name);
end

% Sort by frequency
[freqs, sortIdx] = sort(freqs);
files = files(sortIdx);

% Preallocate results
Ain_all = zeros(length(files),1);
Aout_all = zeros(length(files),1);
gains = zeros(length(files),1);
phases = zeros(length(files),1);
timelags = zeros(length(files),1);

% Plot setup
figure;
tiledlayout(length(files), 1);

for k = 1:length(files)
    f = freqs(k);
    fname = files(k).name;
    data = load(fname);
    xout = data.xout;

    % Duration: 8 s for low frequencies, 5 s for high frequencies
    if f < 10
        T = 8;
    else
        T = 5;
    end

    % Construct time vector
    N = length(xout);
    t = linspace(0, T, N)';

    % Generate input sine wave
    xin = A * sin(2*pi*f*t);

    % --- Fit sinusoids to extract amplitude and phase ---
    omega = 2*pi*f;
    X = [sin(omega*t) cos(omega*t)];
    params_in  = X\xin;
    params_out = X\xout;

    Ain = sqrt(params_in(1)^2 + params_in(2)^2);
    Aout = sqrt(params_out(1)^2 + params_out(2)^2);

    phi_in  = atan2(params_in(2), params_in(1));
    phi_out = atan2(params_out(2), params_out(1));

    gain = Aout / Ain;
    phase = rad2deg(phi_out - phi_in);
    if phase > 0
        phase = phase - 360;
    end

    % Compute time lag (sec)
    timelag = phase / 360 / f;

    % Store results
    Ain_all(k) = Ain;
    Aout_all(k) = Aout;
    gains(k) = gain;
    phases(k) = phase;
    timelags(k) = timelag;

    % --- Plot output vs reference sine ---
    nexttile;
    plot(t, xout, 'b', 'LineWidth', 1.0); hold on;
    plot(t, xin, 'r--', 'LineWidth', 1.0);
    grid on;
    ylabel(sprintf('%.2f Hz', f));
    if k == length(files)
        xlabel('Time (s)');
    end
    title(sprintf('Output vs Input (%.2f Hz)', f));
    legend('x_{out}', 'x_{in}', 'Location', 'best');
end

% --- Plot frequency response ---
figure;
subplot(2,1,1);
semilogx(freqs, 20*log10(gains), 'o-', 'LineWidth', 1.2);
grid on;
ylabel('Magnitude (dB)');
title('Measured Frequency Response');

subplot(2,1,2);
semilogx(freqs, phases, 'o-', 'LineWidth', 1.2);
grid on;
xlabel('Frequency (Hz)');
ylabel('Phase (deg)');

% --- Create results table ---
results = table(freqs, Ain_all, Aout_all, timelags, gains, phases, ...
    'VariableNames', {'Frequency_Hz', 'Input_mm', 'Output_mm', 'TimeLag_sec', 'Gain_mm_per_mm', 'Phase_deg'});

disp(' ');
disp('=== Frequency Response Data ===');
disp(results);

% Optional: Save to CSV
writetable(results, 'frequency_response_results.csv');
