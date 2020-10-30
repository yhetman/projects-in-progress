import astropy
from astropy.wcs import WCS
from astropy.io import fits
import matplotlib.pyplot as plt

wcs_input_dict = {
    'CTYPE1': 'RA---TAN',
    'CUNIT1': 'deg',
    'CDELT1': -0.0002777777778,
    'CRPIX1': 1,
    'CRVAL1': 337.5202808,
    'NAXIS1': 1024,
    'CTYPE2': 'DEC--TAN',
    'CUNIT2': 'deg',
    'CDELT2': 0.0002777777778,
    'CRPIX2': 1,
    'CRVAL2': -20.833333059999998,
    'NAXIS2': 1024
}
wcs_helix_dict = WCS(wcs_input_dict)


class Coords(object):
	def __init__(self, latitude, longtitude):
		super(Coords, self).__init__()
		self.latitude = latitude
		self.longtitude = longtitude

class HorizontalCoords(object):
	def __init__(self, ra, dec):
		super(HorizontalCoords, self).__init__()
		self.ra = ra
		self.dec = dec
		self.Z = 90 - dec		
		
person_coords = Coords(50.45, 30.516667)
star = 

