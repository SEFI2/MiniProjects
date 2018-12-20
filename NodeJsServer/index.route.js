const express = require('express');
const companyRoutes = require('./server/company/company.route');
const couponRoutes = require('./server/coupon/coupon.route');
const userRoutes = require('./server/user/user.route');
const authRoutes = require('./server/auth/auth.route');

const router = express.Router(); // eslint-disable-line new-cap

// TODO: use glob to match *.route files

/** GET /health-check - Check service health */
router.get('/health-check', (req, res) =>
  res.send('OK')
);

// mount coupon routes at /coupons
router.use('/coupons', couponRoutes);

// mount company routes at /companies
router.use('/companies', companyRoutes);

// mount user routes at /users
router.use('/users', userRoutes);

// mount auth routes at /auth
router.use('/auth', authRoutes);

module.exports = router;
