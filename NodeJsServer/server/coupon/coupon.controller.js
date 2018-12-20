const Coupon = require('./coupon.model');

/**
 * Load user and append to req.
 */
function load(req, res, next, id) {
  Coupon.get(id)
    .then((coupon) => {
      req.coupon = coupon; // eslint-disable-line no-param-reassign
      return next();
    })
    .catch(e => next(e));
}

/**
 * Get user
 * @returns {Coupon}
 */
function get(req, res) {
  // populating working example
  var result = req.coupon;
  Coupon.findOne(req.coupon)
  .populate('ownerCompany').exec(
    function(err, post) {

      res.json(post);
    }
  );
}

function getActiveCoupons(req, res) {

  return res.json(req.coupon);
}


/**
 * Create new coupon
 * @property {string} req.body.title - The username of user.
 * @property {string} req.body.information - The mobileNumber of user.
 * @returns {User}
 */
function create(req, res, next) {
  const coupon = new Coupon({
    title: req.body.title,
    information: req.body.information,
    ownerCompany: req.body.ownerCompany,
  });

  if (req.body.startDate) {
    coupon.startDate = req.body.startDate;
  }
  if (req.body.endDate) {
    coupon.endDate = req.body.endDate;
  }

  coupon.save()
    .then(savedCoupon => res.json(savedCoupon))
    .catch(e => next(e));
}

/**
 * Update existing user
 * @property {string} req.body.title - The username of user.
 * @property {string} req.body.information  - The mobileNumber of user.
 * @returns {Coupon}
 */
function update(req, res, next) {
  const coupon = req.coupon;
  coupon.title = req.body.title;
  coupon.information = req.body.information;
  coupon.ownerCompany = req.body.ownerCompany;

  if (req.body.startDate) {
    coupon.startDate = new Date(req.body.startDate);
  }
  if (req.body.endDate) {
    coupon.endDate = new Date(req.body.endDate);
  }
  coupon.save()
    .then(savedCoupon => res.json(savedCoupon))
    .catch(e => next(e));
}

/**
 * Get coupon list.
 * @property {number} req.query.skip - Number of users to be skipped.
 * @property {number} req.query.limit - Limit number of users to be returned.
 * @property {boolean} req.query.active - if  coupons must be active  (endDate >= Date.now)
 * @returns {Coupon[]}
 */

function list(req, res, next) {
  const { limit = 50, skip = 0 } = req.query;
  if (req.query.active) {
    Coupon.find({endDate: {$gte: Date.now()}}).limit(limit).skip(skip).exec(function(err, coupons) {
        if (err) {
          next(err);
        }
        else {
          res.json(coupons);
        }
      });
  }
  else {
    Coupon.list({ limit, skip })
      .then(coupons => res.json(coupons))
      .catch(e => next(e));
  }
}

/**
 * Delete coupon.
 * @returns {Coupon}
 */
function remove(req, res, next) {
  const coupon = req.coupon;
  coupon.remove()
    .then(deletedCoupon => res.json(deletedCoupon))
    .catch(e => next(e));
}

module.exports = { load, get, getActiveCoupons, create, update, list, remove };
