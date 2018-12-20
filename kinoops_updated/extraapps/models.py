from django.db import models

# Create your models here.


class CarouselImage(models.Model):
    image = models.FileField(upload_to='carousel',default='carousel/default_image.jpg')
    subtitle = models.CharField(max_length=200)

    def __str__(self):
        return self.subtitle
