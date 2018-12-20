const express = require('express');
const validate = require('express-validation');
const paramValidation = require('../../config/param-validation');
const couponCtrl = require('./coupon.controller');

const router = express.Router(); // eslint-disable-line new-cap

router.route('/')
  /** GET /api/coupons - Get list of users */
  .get(couponCtrl.list)

  /** POST /api/coupons - Create new user */
  .post(validate(paramValidation.createCoupon), couponCtrl.create);

router.route('/:couponId')
  /** GET /api/coupons/:userId - Get user */
  .get(couponCtrl.get)

  /** PUT /api/coupons/:userId - Update user */
  .put(validate(paramValidation.createCoupon), couponCtrl.update)

  /** DELETE /api/coupons/:userId - Delete user */
  .delete(couponCtrl.remove);

router.route('/active')
    /** GET /api/active - Get list of active coupons */
    .get(couponCtrl.getActiveCoupons)


/** Load user when API with userId route parameter is hit */
router.param('couponId', couponCtrl.load);

module.exports = router;
