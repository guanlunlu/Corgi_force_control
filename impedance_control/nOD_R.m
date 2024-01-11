function out = nOD_R(th)
out = [sin(th).*(8.0./3.25e+2);cos(th).*(2.0./2.5e+1)-sqrt(sin(th).^2.*(-6.4e+1./1.69e+2)+1.0).*(9.0./1.0e+2)];
end
