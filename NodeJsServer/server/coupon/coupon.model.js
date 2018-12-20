const Promise = require('bluebird');
const mongoose = require('mongoose');
const httpStatus = require('http-status');
const APIError = require('../helpers/APIError');

/**
 * Coupon Schema
 */
const CouponSchema = new mongoose.Schema({
  title: {
    type: String,
    required: true
  },
  information: {
    type: String,
    required: true,
  },
  startDate: {
    type: Date,
    required: false
  },
  endDate: {
    type: Date,
    required: false
  },
  createdAt: {
    type: Date,
    default: Date.now
  },
  ownerCompany: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'Company'
  }
});

/**
 * Add your
 * - pre-save hooks
 * - validations
 * - virtuals
 */

/**
 * Methods
 */
CouponSchema.method({
});

/**
 * Statics
 */
CouponSchema.statics = {
  /**
   * Get coupon
   * @param {ObjectId} id - The objectId of coupon.
   * @returns {Promise<Coupon, APIError>}
   */
  get(id) {
    return this.findById(id)
      .exec()
      .then((coupon) => {
        if (coupon) {
          return coupon;
        }
        const err = new APIError('No such coupon exists!', httpStatus.NOT_FOUND);
        return Promise.reject(err);
      });
  },

  /**
   * List coupons in descending order of 'createdAt' timestamp.
   * @param {number} skip - Number of coupons to be skipped.
   * @param {number} limit - Limit number of coupons to be returned.
   * @returns {Promise<Coupon[]>}
   */
  list({ skip = 0, limit = 50 } = {}) {
    return this.find()
      .sort({ createdAt: -1 })
      .skip(+skip)
      .limit(+limit)
      .exec();
  }
};

/**
 * @typedef Coupon
 */
module.exports = mongoose.model('Coupon', CouponSchema);
