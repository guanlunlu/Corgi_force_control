function write_anon_function_to_file(func)
% This will write an anonymous function a an m file.
% Note that this will only work if the function does not have capture
% variables. So this will not work:
%   a = 100;
%   func = @(x) x+a;
%   write_anon_function_to_file(func)
% But this will:
%   func = @(x) x+100;
%   write_anon_function_to_file(func)
% Determine the function name.
try
    name = inputname(1);
    if isempty(name),error('trigger catch block'),end
catch
    name = 'myfunc';
end
% Extract and parse the function contents.
txt = formattedDisplayText(func); % capture the output
txt = char(txt); % convert to char
txt = strtrim(txt); % remove leading and trailing whitespace
ind = strfind(txt,')'); ind = ind(1); % find the end of the input arguments
% Compose the function and write to file.
txt = sprintf('function out = %s(%s)\nout = %s;\nend', ...
    name,txt(3:(ind-1)),txt((ind+1):end));
writelines(txt,[name '.m']);
end